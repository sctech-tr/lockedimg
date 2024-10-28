# Locked Image Tool (`lockedimg`)

`lockedimg` is a simple command-line utility for encrypting and decrypting images with password protection. This tool supports various image formats and saves encrypted files with a `.lockedimg` extension, which can be decrypted with the correct password.

## Features
- **Encrypt** and **decrypt** image files using AES-256 encryption.
- Supports common image file formats: `.jpg`, `.jpeg`, `.png`, `.bmp`, `.gif`, `.ico`, `.bruh`, `.jfif`, `.svg`, and `.lockedimg`.
- **Optional deletion** of encrypted files after decryption.

## Requirements
- **OpenSSL** library is required for encryption and decryption functionality.
- A **C compiler** such as GCC.

## Compilation (for devs)
Compile the project using `make`:
```bash
make
```
This will produce an executable named `lockedimg`.
## Installation
Download the latest zip archive from the releases tab, extract it and run `./lockedimg` <!-- todo: improve -->
## Usage
```bash
lockedimg <action> <image file path> <password> [--no-deletion]
```
## Parameters

- `<action>`: Choose between encrypt or decrypt.
- `<image file path>`: Path to the image file.
- `<password>`: Password for encryption or decryption.
- `--no-deletion`: Optional. Prevents deletion of the encrypted file after decryption.

## Examples
### Encrypt an image
```bash
lockedimg encrypt image.jpg mypassword123
```
### Decrypt an image without deletion
```bash
lockedimg decrypt image.jpg.lockedimg mypassword123 --no-deletion
```
## Help
Run the following for help information:
```bash
lockedimg --help
```
## Cleanup (for devs)
To remove the executable and object files:
```bash
make clean
```
## License
Apache-2.0 License
