FROM mcr.microsoft.com/devcontainers/base:ubuntu-24.04

# Packages specified by pokeemerald-expansion's Ubuntu build instructions.
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    binutils-arm-none-eabi \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    git \
    libpng-dev \
    python3 \
    && rm -rf /var/lib/apt/lists/
