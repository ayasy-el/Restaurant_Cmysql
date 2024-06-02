CREATE DATABASE restoran_db;

USE restoran_db;

CREATE TABLE Menu (
    MenuID INT AUTO_INCREMENT PRIMARY KEY,
    NamaMenu VARCHAR(50) NOT NULL,
    HargaMenu INT NOT NULL
);

CREATE TABLE Removed_Menu (
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
    FOREIGN KEY (PesananID) REFERENCES Pesanan(PesananID)
);

DELIMITER //

CREATE TRIGGER before_menu_delete
BEFORE DELETE ON menu
FOR EACH ROW
BEGIN
    INSERT INTO Removed_Menu (MenuID, NamaMenu, HargaMenu)
    VALUES (OLD.MenuID, OLD.NamaMenu, OLD.HargaMenu);
END;

//

DELIMITER ;
