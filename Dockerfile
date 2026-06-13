FROM gcc:13
# Install dependensi yang diperlukan untuk build
RUN apt-get update && apt-get install -y libssl-dev libmariadb-dev

# Copy semua file ke dalam container
COPY . .

# Build proyek
RUN make -j$(nproc)
# Jalankan server
CMD ["./main.out"]

