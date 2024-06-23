# Raster Graphics Console Editor

A console-based raster image editor application. The editor supports working with various files, managing sessions, applying different transformations to images, and saving the results.

## Supported Formats

The application works with PPM, PGM, and PBM files (for more information, see [Netpbm format](http://en.wikipedia.org/wiki/Netpbm_format)).

## Commands

### Loading Files

Loading a file with the `load` command creates a "user session" with a unique ID. Multiple images can be loaded within a single session. Executing the `load` command creates a new session. At least one file name is expected as an argument.


### Applying Transformations

Transformations apply to all loaded images within the current session and take effect only after executing the `save` or `saveas` command. The `save` command saves all images in the current session after applying all transformations, while `saveas` saves only the first loaded image under a new name.

### Supported Operations

1. **grayscale**: Converts all color images in the current session to grayscale. Black-and-white images remain unchanged.
2. **monochrome**: Converts images to monochrome (black and white). Images already in monochrome are not changed.
3. **negative**: Creates a negative of the images in the current session.
4. **rotate `<direction>`**: Rotates images 90 degrees in the specified direction (`left` or `right`).
5. **undo**: Reverts the last transformation in the current session. If no transformations have been applied, it has no effect.
6. **add `<image>`**: Adds an image to the current session without applying existing transformations.
7. **session info**: Displays information about the current session, including the session ID, loaded images, and pending transformations.
8. **switch `<session>`**: Switches to the specified session ID. If the session does not exist, an error message is displayed.
9. **collage `<direction>` `<image1>` `<image2>` `<outimage>`**: Creates a collage from two images in the current session, either horizontally or vertically. The result is saved in a new image added to the session.

### General Commands

- **load `<file>`**: Loads an image file and starts a new session.
- **close**: Closes the current session.
- **save**: Saves all images in the current session.
- **saveas `<new_file>`**: Saves the first loaded image under a new name.
- **help**: Displays help information.
- **exit**: Exits the application.

## Conclusion

This raster graphics console editor allows users to manipulate images through a command-line interface, providing a range of transformations and session management capabilities. The application ensures a flexible and efficient way to handle raster images in different formats.
