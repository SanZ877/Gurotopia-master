FROM gcc:13
# Install dependensi yang diperlukan untuk build
RUN apt-get update && apt-get install -y \
    build-essential \
    libssl-dev \
    libmariadb-dev \
    make \
    gcc-13 \
    g++-13 \
    && rm -rf /var/lib/apt/lists/*

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 100

# Copy semua file ke dalam container
COPY . .

# Build proyek
RUN make

EXPOSE 17091/udp
# Jalankan server
CMD ["./main.out"]

