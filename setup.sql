CREATE DATABASE restoran_db;

USE restoran_db;

CREATE TABLE Menu (
    MenuID INT AUTO_INCREMENT PRIMARY KEY,
    NamaMenu VARCHAR(50) NOT NULL,
    HargaMenu INT NOT NULL
);

CREATE TABLE Pesanan (
    PesananID INT AUTO_INCREMENT PRIMARY KEY,
    Timestamp DATETIME NOT NULL,
    NamaPelanggan VARCHAR(100) NOT NULL,
    TotalHarga INT NOT NULL,
    MetodePembayaran VARCHAR(20) NOT NULL,
    Status VARCHAR(20) NOT NULL
);

CREATE TABLE Detail_Pesanan (
    DetailPesananID INT AUTO_INCREMENT PRIMARY KEY,
    PesananID INT,
    MenuID INT,
    Jumlah INT NOT NULL,
    FOREIGN KEY (PesananID) REFERENCES Pesanan(PesananID),
    FOREIGN KEY (MenuID) REFERENCES Menu(MenuID)
);
