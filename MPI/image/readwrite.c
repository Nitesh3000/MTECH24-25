#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define IMAGE_WIDTH 200
#define IMAGE_HEIGHT 100
#define NUM_PARTS 4

typedef struct {
    int width;
    int height;
    unsigned char* data;
} PGMImage;

PGMImage* readPGM(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    char magic[3];
    int width, height, max_gray_value;
    fscanf(file, "%2s %d %d %d\n", magic, &width, &height, &max_gray_value);

    if (strcmp(magic, "P5") != 0) {
        fprintf(stderr, "Not a PGM file\n");
        fclose(file);
        return NULL;
    }

    unsigned char* data = (unsigned char*)malloc(width * height * sizeof(unsigned char));
    if (!data) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    fread(data, sizeof(unsigned char), width * height, file);

    fclose(file);

    PGMImage* image = (PGMImage*)malloc(sizeof(PGMImage));
    if (!image) {
        perror("Memory allocation failed");
        free(data);
        return NULL;
    }

    image->width = width;
    image->height = height;
    image->data = data;

    return image;
}

void freePGMImage(PGMImage* image) {
    if (image) {
        free(image->data);
        free(image);
    }
}

void writePGM(const char* filename, PGMImage* image) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "P5\n%d %d\n255\n", image->width, image->height);

    fwrite(image->data, sizeof(unsigned char), image->width * image->height, file);

    fclose(file);
}

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_image.pgm>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    const char* inputFileName = argv[1];

    PGMImage* originalImage = readPGM(inputFileName);

    if (!originalImage) {
        fprintf(stderr, "Failed to read PGM image\n");
        MPI_Finalize();
        return 1;
    }

    int partWidth = originalImage->width;
    int partHeight = originalImage->height / size;

    unsigned char* partData = (unsigned char*)malloc(partWidth * partHeight * sizeof(unsigned char));

    MPI_Scatter(originalImage->data, partWidth * partHeight, MPI_UNSIGNED_CHAR,
                partData, partWidth * partHeight, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
    for (int i = 0; i < partWidth * partHeight; i++) {
        partData[i] = 255 - partData[i]; // Invert colors
    }

    char folderName[50];
    snprintf(folderName, sizeof(folderName), "segmented_part_%d", rank);

    if (mkdir(folderName, 0777) != 0 && errno != EEXIST) {
        perror("Error creating folder");
        MPI_Finalize();
        return 1;
    }

    char outputFileName[100];
    snprintf(outputFileName, sizeof(outputFileName), "%s/segmented_part.pgm", folderName);

    PGMImage modifiedPart;
    modifiedPart.width = partWidth;
    modifiedPart.height = partHeight;
    modifiedPart.data = partData;

    writePGM(outputFileName, &modifiedPart);
    MPI_Barrier(MPI_COMM_WORLD);

unsigned char* fullImageData = NULL;
if (rank == 0) {
    fullImageData = (unsigned char*)malloc(originalImage->width * originalImage->height * sizeof(unsigned char));
}

MPI_Gather(partData, partWidth * partHeight, MPI_UNSIGNED_CHAR,
            fullImageData, partWidth * partHeight, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

if (rank == 0) {
    char folderName0[50];
    snprintf(folderName0, sizeof(folderName0), "segmented_part_0");

    if (mkdir(folderName0, 0777) != 0 && errno != EEXIST) {
        perror("Error creating folder");
        MPI_Finalize();
        return 1;
    }

    char fullImageFileName[100];
    snprintf(fullImageFileName, sizeof(fullImageFileName), "%s/full_image.pgm", folderName0);

    PGMImage fullImage;
    fullImage.width = originalImage->width;
    fullImage.height = originalImage->height;
    fullImage.data = fullImageData;

    writePGM(fullImageFileName, &fullImage);

    free(fullImageData);
}



    freePGMImage(originalImage);
    free(partData);
    MPI_Finalize();

    return 0;
}
