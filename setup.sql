CREATE DATABASE restoran_db;

USE restoran_db;

CREATE TABLE Pelanggan (
    PelangganID INT AUTO_INCREMENT PRIMARY KEY,
    Nama VARCHAR(100) NOT NULL
);

CREATE TABLE Pesanan (
    PesananID INT AUTO_INCREMENT PRIMARY KEY,
    Timestamp DATETIME NOT NULL,
    PelangganID INT,
    TotalHarga INT NOT NULL,
    MetodePembayaran VARCHAR(20) NOT NULL,
    Status VARCHAR(20) NOT NULL,
    FOREIGN KEY (PelangganID) REFERENCES Pelanggan(PelangganID)
);

CREATE TABLE Detail_Pesanan (
    DetailPesananID INT AUTO_INCREMENT PRIMARY KEY,
    PesananID INT,
    Menu VARCHAR(50) NOT NULL,
    Jumlah INT NOT NULL,
    HargaSatuan INT NOT NULL,
    FOREIGN KEY (PesananID) REFERENCES Pesanan(PesananID)
);