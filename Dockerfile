FROM gcc:13

# Update dan install dependensi
RUN apt-get update && apt-get install -y \
    libssl-dev \
    libmariadb-dev \
    make \
    && rm -rf /var/lib/apt/lists/*

# Copy semua file ke dalam container
COPY . .

# Build proyek
RUN make

EXPOSE 17091/udp
# Jalankan server
CMD ["./main.out"]

