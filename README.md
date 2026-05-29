
# Yocto Project Backup

This repository contains the backup of my Yocto Project setup, including custom layers, configuration files, recipes, and patches required to rebuild the project environment.

# Contents

- Custom Yocto layers (`meta-*`)
- Build configuration files
- Recipes and patches
- BSP/custom modifications
- Scripts and utilities

---

# System Requirements

Recommended OS:

- Ubuntu 20.04 / 22.04 LTS

Required packages:

```bash
sudo apt update

sudo apt install gawk wget git diffstat unzip texinfo gcc build-essential \
chrpath socat cpio python3 python3-pip python3-pexpect xz-utils \
debianutils iputils-ping python3-git python3-jinja2 libegl1-mesa \
libsdl1.2-dev pylint xterm
````

---

# Clone the Repository

```bash
git clone https://github.com/YOUR_USERNAME/YOUR_REPOSITORY.git
```

Example:

```bash
git clone https://github.com/praveen123/yocto-backup.git
```

Go into the project directory:

```bash
cd yocto-backup
```

---

# Yocto Environment Setup

Initialize the build environment:

```bash
source oe-init-build-env
```

If build directory already exists:

```bash
source oe-init-build-env build
```

---

# Configure Build

Check configuration files:

```bash
build/conf/local.conf
build/conf/bblayers.conf
```

Modify according to your target board and machine.

Example:

```conf
MACHINE = "qemuarm64"
```

---

# Build the Image

Example build command:

```bash
bitbake core-image-minimal
```

Or for a custom image:

```bash
bitbake <image-name>
```

---

# Output Files

Generated images are located in:

```bash
build/tmp/deploy/images/
```

---

# Clean Build

To clean a package:

```bash
bitbake -c clean <recipe-name>
```

To clean entire build artifacts:

```bash
rm -rf build/tmp
```

---

# Notes

* `tmp/`, `downloads/`, and `sstate-cache/` are excluded from backup because they can be regenerated.
* This repository is intended for source/configuration backup and reproducible builds.
* Ensure all required Yocto dependencies are installed before building.

---

# Git Usage

Pull latest changes:

```bash
git pull
```

Push new changes:

```bash
git add .
git commit -m "Updated project"
git push
```

