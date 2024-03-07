// /* This coursework specification, and the example code provided during the
//  * course, is Copyright 2024 Heriot-Watt University.
//  * Distributing this coursework specification or your solution to it outside
//  * the university is academic misconduct and a violation of copyright law. */

// This code has been modified by: Mohamad Ajaz Imran
// HW ID: H00458396

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* The RGB values of a pixel. */
struct Pixel
{
    int red;
    int green;
    int blue;
};

/* An image loaded from a file. */
struct Image
{
    int width;
    int height;
    struct Pixel *pixels;
};

/**
 * Frees the memory allocated for an Image structure.
 *
 * @param img A pointer to the Image to be freed.
 */
void free_image(struct Image *img)
{
    if (img != NULL)
    {
        free(img->pixels);
        free(img);
    }
}

/**
 * Opens an image file, reads its contents, and returns a new Image structure.
 *
 * @param filename The name of the image file to open.
 * @return A pointer to a new Image structure, or NULL if an error occurs.
 *
 * Error Handling:
 * - File not found
 * - Invalid image format (must be HSDEC)
 * - Memory allocation failure
 * - Error reading pixel data
 */
struct Image *load_image(const char *filename)
{
    // Open the file for reading 
    FILE *f = fopen(filename, "r");

    // Error handling 1: file cannot be opened
    if (f == NULL)
    {
        fprintf(stderr, "File %s could not be opened! Check your file name!\n", filename);
        return NULL;
    }

    
    char format[6]; // Stores the format of the image (HSDEC)
    int width, height; // Stores the width and height of the image (Useful when traversing the image)

    // Error handling 2: file format is not HSDEC
    // fscanf returns the number of items read in the first line, so we check if it is 3 (HSDEC format) or not.
    // If it is not 3, it means the file format is not HSDEC, so we print an error message and close the file.
    // If it is 3, we store the width and height of the image in the variables width and height.
    if (fscanf(f, "%5s %d %d", format, &width, &height) != 3 || strcmp(format, "HSDEC") != 0)
    {
        fprintf(stderr, "Invalid image format! Check the file type!\n");
        fclose(f); // Close the file
        return NULL;
    }

    // Declare a variable called img and initializes it to a pointer of type struct Image.
    struct Image *img = (struct Image *)malloc(sizeof(struct Image));

    // Set the new img width and height to the original width and height
    img->width = width;
    img->height = height;
    // Allocate memory for the pixels of the image and store it in the img pixels field.
    // The size of the pixels field is width * height * sizeof(struct Pixel).
    img->pixels = (struct Pixel *)malloc(width * height * sizeof(struct Pixel));

    // Error handling 3: memory allocation failed
    if (img->pixels == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(f);
        free(img);
        return NULL;
    }

    // Error handling 4: invalid image size
    // If the width or height of the image is less than 1, it means the image size is invalid, so we print an error message and close the file.
    for (int i = 0; i < width * height; i++)
    {
        // values are scanned into the red, green, and blue fields of the current pixel struct img->pixels[i].
        // It checks that fscanf was able to successfully read 3 values on each iteration. Else it prints an error and closes the file.
        if (fscanf(f, "%d %d %d", &(img->pixels[i].red), &(img->pixels[i].green), &(img->pixels[i].blue)) != 3)
        {
            fprintf(stderr, "Error reading pixel data.\n");
            fclose(f);
            free_image(img);
            return NULL;
        }
    }

    // Error handling 5: Image cannot be read
    if (img == NULL)
    {
        fprintf(stderr, "Image %s could not be read.\n", filename);
        fclose(f);
        return NULL;
    }

    /* Close the file */
    fclose(f);
    return img;
}

/**
 * Saves an Image to a file.
 *
 * @param img     A pointer to the Image to be saved.
 * @param filename The name of the output file.
 * @return true on success, false on failure.
 */
bool save_image(const struct Image *img, const char *filename)
{

    // File open for writing
    FILE *f = fopen(filename, "w");

    // Error handling: File cannot be open for writing
    if (f == NULL)
    {
        fprintf(stderr, "File %s could not be opened for writing.\n", filename);
        return false;
    }

    // Write the image type, width and height into the file as the header
    fprintf(f, "HSDEC %d %d\n", img->width, img->height);

    // Write the pixel data width * height number of times
    for (int i = 0; i < img->width * img->height; i++)
    {
        fprintf(f, "%d %d %d\n", img->pixels[i].red, img->pixels[i].green, img->pixels[i].blue);
    }

    fclose(f);
    return true;
}

/**
 * Allocate a new struct Image and copy an existing struct Image's contents
 *
 * @param source  A pointer to the source Image.
 * @return A pointer to a new Image containing a copy of the original data,
 *         or NULL on memory allocation failure.
 */
struct Image *copy_image(const struct Image *source)
{
    struct Image *copy = (struct Image *)malloc(sizeof(struct Image));

    // Error handling 1: Allocation of memory to the copy failed
    if (copy == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    copy->width = source->width;
    copy->height = source->height;
    
    // Dynamically allocating memory for the pixels array of copy.
    // By allocating based on the source image size, the copy image will have an identically sized pixels array to store the pixel data.
    copy->pixels = (struct Pixel *)malloc(source->width * source->height * sizeof(struct Pixel));
    if (copy->pixels == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        free(copy);
        return NULL;
    }

    // memcpy is used to copy the contents of the source pixels array in one go.
    // This ensures that the copy image has the same pixel data as the source image.
    memcpy(copy->pixels, source->pixels, source->width * source->height * sizeof(struct Pixel));

    return copy;
}

/**
 * Helper function for sorting integer arrays using qsort().
 *
 * @param a  Pointer to the first element to compare
 * @param b Pointer to the second element to compare
 * @return An integer less than, equal to, or greater than zero
 *         if the first argument is considered to be respectively
 *         less than, equal to, or greater than the second.
 */
int compare_integers(const void *a, const void *b)
{
    int int_a = *((int *)a);
    int int_b = *((int *)b);

    if (int_a == int_b)
        return 0;
    else if (int_a < int_b)
        return -1;
    else
        return 1;
}

/**
 * Applies a median filter to the image to reduce noise.
 *
 * @param source  A pointer to the original Image.
 * @return A pointer to a new Image containing the filtered result,
 *         or NULL on memory allocation failure.
 */
struct Image *apply_MEDIAN(const struct Image *source)
{
    // Create a copy of the source image
    struct Image *result = copy_image(source);
    if (result == NULL)
    {
        return NULL;
    }

    // malloc call allocates enough memory for an array of source->height Pixel pointers. 
    // It then assigns this block of memory to the pixel_matrix pointer.
    struct Pixel **pixel_matrix = (struct Pixel **)malloc(source->height * sizeof(struct Pixel *));
    if (pixel_matrix == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        free_image(result);
        return NULL;
    }

    // Allocate memory for each row of the 2D pixel matrix, 
    // and storing the row pointers in the pixel_matrix array.
    for (int i = 0; i < source->height; i++)
    {
        pixel_matrix[i] = (struct Pixel *)malloc(source->width * sizeof(struct Pixel));
        if (pixel_matrix[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            // Free memory allocated so far
            for (int j = 0; j < i; j++)
            {
                free(pixel_matrix[j]);
            }
            free(pixel_matrix);
            free_image(result);
            return NULL;
        }
    }

    // Copy pixel values to the matrix
    for (int y = 0; y < source->height; y++)
    {
        for (int x = 0; x < source->width; x++)
        {
            pixel_matrix[y][x] = source->pixels[y * source->width + x];
        }
    }

    // Apply median filter
    for (int y = 0; y < source->height; y++)
    {
        for (int x = 0; x < source->width; x++)
        {
            // Create arrays to hold neighboring pixel values
            // (Target pixel, left, right, up, down)
            int red_values[5];
            int green_values[5];
            int blue_values[5];

            // Collect neighboring pixel values
            red_values[0] = pixel_matrix[y][x].red;
            green_values[0] = pixel_matrix[y][x].green;
            blue_values[0] = pixel_matrix[y][x].blue;

            // Gather the left pixel value from the target pixel
            if (x > 0)
            {
                red_values[1] = pixel_matrix[y][x - 1].red;
                green_values[1] = pixel_matrix[y][x - 1].green;
                blue_values[1] = pixel_matrix[y][x - 1].blue;
            } 
            // else the target pixel is on the left edge, set the right pixel value to 0            
            else      
            {
                red_values[1] = 0;
                green_values[1] = 0;
                blue_values[1] = 0;
            }
            
            // Gather the right pixel value from the target pixel
            if (x < source->width - 1)
            {
                red_values[2] = pixel_matrix[y][x + 1].red;
                green_values[2] = pixel_matrix[y][x + 1].green;
                blue_values[2] = pixel_matrix[y][x + 1].blue;
            }
            // else the target pixel is on the right edge, set the right pixel value to 0
            else
            {
                red_values[2] = 0;
                green_values[2] = 0;
                blue_values[2] = 0;
            }

            // Gather the up pixel value from the target pixel
            if (y > 0)
            {
                red_values[3] = pixel_matrix[y - 1][x].red;
                green_values[3] = pixel_matrix[y - 1][x].green;
                blue_values[3] = pixel_matrix[y - 1][x].blue;
            }
            // else the target pixel is on the top edge, set the up pixel value to 0
            else
            {
                red_values[3] = 0;
                green_values[3] = 0;
                blue_values[3] = 0;
            }

            // Gather the down pixel value from the target pixel
            if (y < source->height - 1)
            {
                red_values[4] = pixel_matrix[y + 1][x].red;
                green_values[4] = pixel_matrix[y + 1][x].green;
                blue_values[4] = pixel_matrix[y + 1][x].blue;
            }
            // else the target pixel is on the bottom edge, set the down pixel value to 0
            else
            {
                red_values[4] = 0;
                green_values[4] = 0;
                blue_values[4] = 0;
            }

            // Sort the pixel values
            qsort(red_values, 5, sizeof(int), compare_integers);
            qsort(green_values, 5, sizeof(int), compare_integers);
            qsort(blue_values, 5, sizeof(int), compare_integers);

            // Set the target pixel value to the median
            result->pixels[y * source->width + x].red = red_values[2];
            result->pixels[y * source->width + x].green = green_values[2];
            result->pixels[y * source->width + x].blue = blue_values[2];
        }
    }

    // Free memory allocated for the pixel matrix
    for (int i = 0; i < source->height; i++)
    {
        free(pixel_matrix[i]);
    }
    free(pixel_matrix);

    return result;
}

/**
 * Normalizes an image by rescaling pixel values to the range of 0-255.
 *
 * @param source  A pointer to the Image to be normalized.
 * @return true on success, false if an error occurs.
 *         (Currently, this always returns true.)
 */
bool apply_NORM(struct Image *source)
{

    // Initialize variables to track minimum and maximum pixel values for each color component
    int min_red = 255, min_green = 255, min_blue = 255;
    int max_red = 0, max_green = 0, max_blue = 0;

    // Find min and max values across all pixels in the image
    for (int i = 0; i < source->width * source->height; i++)
    {   
        // Update minimum values if necessary
        if (source->pixels[i].red < min_red)
            min_red = source->pixels[i].red;
        if (source->pixels[i].green < min_green)
            min_green = source->pixels[i].green;
        if (source->pixels[i].blue < min_blue)
            min_blue = source->pixels[i].blue;

        // Update maximum values if necessary
        if (source->pixels[i].red > max_red)
            max_red = source->pixels[i].red;
        if (source->pixels[i].green > max_green)
            max_green = source->pixels[i].green;
        if (source->pixels[i].blue > max_blue)
            max_blue = source->pixels[i].blue;
    }

    // Print the minimum and maximum values of the image 
    printf("Minimum value: %d\n", min_red < min_green ? (min_red < min_blue ? min_red : min_blue) : (min_green < min_blue ? min_green : min_blue));
    printf("Maximum value: %d\n", max_red > max_green ? (max_red > max_blue ? max_red : max_blue) : (max_green > max_blue ? max_green : max_blue));

    // Normalize the image by rescaling all pixel values to the range 0-255
    for (int i = 0; i < source->width * source->height; i++)
    {
        source->pixels[i].red = (int)(((double)(source->pixels[i].red - min_red) / (double)(max_red - min_red)) * 255);
        source->pixels[i].green = (int)(((double)(source->pixels[i].green - min_green) / (double)(max_green - min_green)) * 255);
        source->pixels[i].blue = (int)(((double)(source->pixels[i].blue - min_blue) / (double)(max_blue - min_blue)) * 255);
    }

    return true;
}

int main(int argc, char *argv[])
{
    /* Initialise the random number generator, using the time as the seed */
    srand(time(NULL));

    /* Check command-line arguments */
    if (argc != 3)
    {
        fprintf(stderr, "Usage: process INPUTFILE OUTPUTFILE\n");
        return 1;
    }

    /* Load the input image */
    struct Image *in_img = load_image(argv[1]);
    if (in_img == NULL)
    {
        return 1;
    }

    /* Apply the first process */
    struct Image *out_img = apply_MEDIAN(in_img);
    if (out_img == NULL)
    {
        fprintf(stderr, "First process failed.\n");
        free_image(in_img);
        return 1;
    }

    /* Apply the second process */
    if (!apply_NORM(out_img))
    {
        fprintf(stderr, "Second process failed.\n");
        free_image(in_img);
        free_image(out_img);
        return 1;
    }

    /* Save the output image */
    if (!save_image(out_img, argv[2]))
    {
        fprintf(stderr, "Saving image to %s failed.\n", argv[2]);
        free_image(in_img);
        free_image(out_img);
        return 1;
    }

    free_image(in_img);
    free_image(out_img);
    return 0;
}
