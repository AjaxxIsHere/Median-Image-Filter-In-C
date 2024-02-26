# F28HS Coursework 1

H00458396: HSDEC MEDIAN NORM

Task HSDEC
An HSDEC image consists entirely of ASCII text. It starts with a header:
HSDEC
width height
where:• HSDEC — fixed code indicating HSDEC format
• width — integer number of columns
• height — integer number of rows
The image data follows the header. Each pixel is stored as three unsigned 8-bit values as decimal
numbers. Pixels are stored from left to right in the first row, then left to right in the second row, and
so on until the end of the image.
All fields in the file are separated by one or more whitespace (space, tab, carriage return or
newline) characters.

Task MEDIAN
The apply_MEDIAN function should apply a median filter to an image. Each colour value in the
output image should be computed as the median of the corresponding input pixel and the four
pixels horizontally and vertically adjacent to it (above, below, left and right of it).
To compute the median of a set of numbers, sort them into order and take the middle one. For
example, you could copy the values into a fixed-length array, then call the qsort function from
the standard library to sort them.
Be careful to avoid accessing locations outside the bounds of the image.

Task NORM
The apply_NORM function should first scan through the image to find the smallest and largest
values used in the red, green and blue values (all together; you don't need to track red/green/blue
separately). It should print out a message like:
Minimum value: 10
Maximum value: 255
It should then normalise the image by scaling all the values so that the minimum value becomes 0,
and the maximum value becomes the biggest possible value that can be stored. (Do this in two
steps: subtract an offset to bring the minimum to 0, then multiply by a scaling factor to bring the
maximum to the largest value.)
Because this means modifying the image, you will need to remove the const from the type of
apply_NORM's image argument.