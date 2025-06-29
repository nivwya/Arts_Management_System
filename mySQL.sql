CREATE TABLE Artwork (
    ArtworkID INT PRIMARY KEY,
    Title VARCHAR(255),
    Medium VARCHAR(100),
    Style VARCHAR(100),
    Price DECIMAL(10, 2),
    DateCreated DATE,
    ArtistID INT,
    ExhibitionID INT,
    Status ENUM('For Sale', 'Sold') DEFAULT 'For Sale',
    FOREIGN KEY (ArtistID) REFERENCES Artist(ArtistID),
    FOREIGN KEY (ExhibitionID) REFERENCES Exhibition(ExhibitionID)
);

CREATE TABLE Artist (
    ArtistID INT PRIMARY KEY,
    Name VARCHAR(255),
    DateOfBirth DATE,
    Bio TEXT,
    Country VARCHAR(100)
);

CREATE TABLE Customer (
    CustomerID INT PRIMARY KEY,
    Name VARCHAR(255),
    ContactInfo VARCHAR(255),
    Address VARCHAR(255)
);

CREATE TABLE Exhibition (
    ExhibitionID INT PRIMARY KEY,
    Title VARCHAR(255),
    StartDate DATE, 
    EndDate DATE,
    Location VARCHAR(255),
    Description TEXT
);

CREATE TABLE Transaction (
    TransactionID INT PRIMARY KEY,
    ArtworkID INT,
    CustomerID INT,
    Date DATE,
    Price DECIMAL(10, 2),
    PaymentMethod VARCHAR(50),
    FOREIGN KEY (ArtworkID) REFERENCES Artwork(ArtworkID),
    FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID)
);

CREATE TABLE Inventory (
    InventoryID INT PRIMARY KEY,
    ArtworkID INT,
    Location VARCHAR(255),
    Quantity INT,
    FOREIGN KEY (ArtworkID) REFERENCES Artwork(ArtworkID)
);


-- views

CREATE VIEW AvailableArtworks AS
SELECT ArtworkID, Title, ArtistID, Price, DateCreated
FROM Artwork
WHERE Status = 'For Sale';

CREATE VIEW ArtistSales AS
SELECT a.ArtistID, ar.Name, COUNT(t.TransactionID) AS TotalSales, SUM(t.Price) AS TotalRevenue
FROM Transaction t
JOIN Artwork a ON t.ArtworkID = a.ArtworkID
JOIN Artist ar ON a.ArtistID = ar.ArtistID
GROUP BY a.ArtistID;

-- Stored Procedures

DELIMITER $$
CREATE PROCEDURE AddArtwork(
    IN p_Title VARCHAR(255),
    IN p_Medium VARCHAR(100),
    IN p_Style VARCHAR(100),
    IN p_Price DECIMAL(10,2),
    IN p_DateCreated DATE,
    IN p_ArtistID INT,
    IN p_ExhibitionID INT
)
BEGIN
    INSERT INTO Artwork (Title, Medium, Style, Price, DateCreated, ArtistID, ExhibitionID, Status)
    VALUES (p_Title, p_Medium, p_Style, p_Price, p_DateCreated, p_ArtistID, p_ExhibitionID, 'For Sale');
END $$
DELIMITER ;

DELIMITER $$
CREATE PROCEDURE MarkArtworkAsSold(
    IN p_ArtworkID INT
)
BEGIN
    UPDATE Artwork
    SET Status = 'Sold'
    WHERE ArtworkID = p_ArtworkID;
END $$
DELIMITER ;

-- triggers

DELIMITER $$
CREATE TRIGGER UpdateInventoryAfterSale
AFTER INSERT ON Transaction
FOR EACH ROW
BEGIN
    UPDATE Inventory
    SET Quantity = Quantity - 1
    WHERE ArtworkID = NEW.ArtworkID;
END $$
DELIMITER ;

DELIMITER $$
CREATE TRIGGER PreventDuplicateSales
BEFORE INSERT ON Transaction
FOR EACH ROW
BEGIN
    DECLARE artwork_status VARCHAR(20);
    SELECT Status INTO artwork_status
    FROM Artwork
    WHERE ArtworkID = NEW.ArtworkID;
    
    IF artwork_status = 'Sold' THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Artwork is already sold and cannot be sold again';
    END IF;
END $$
DELIMITER ;

-- cursors

DELIMITER $$
CREATE PROCEDURE ListArtworksByArtist(IN p_ArtistID INT)
BEGIN
    DECLARE done INT DEFAULT FALSE;
    DECLARE artwork_title VARCHAR(255);
    DECLARE artwork_cursor CURSOR FOR
        SELECT Title FROM Artwork WHERE ArtistID = p_ArtistID;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
    
    OPEN artwork_cursor;
    read_loop: LOOP
        FETCH artwork_cursor INTO artwork_title;
        IF done THEN
            LEAVE read_loop;
        END IF;
        SELECT artwork_title;
    END LOOP;
    CLOSE artwork_cursor;
END $$
DELIMITER ;

DELIMITER $$
CREATE PROCEDURE ListAvailableArtworks()
BEGIN
    DECLARE done INT DEFAULT FALSE;
    DECLARE artwork_id INT;
    DECLARE artwork_title VARCHAR(255);
    DECLARE artwork_price DECIMAL(10,2);
    DECLARE available_cursor CURSOR FOR
        SELECT ArtworkID, Title, Price FROM Artwork WHERE Status = 'For Sale';
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
    
    OPEN available_cursor;
    read_loop: LOOP
        FETCH available_cursor INTO artwork_id, artwork_title, artwork_price;
        IF done THEN
            LEAVE read_loop;
        END IF;
        SELECT artwork_id, artwork_title, artwork_price;
    END LOOP;
    CLOSE available_cursor;
END $$
DELIMITER ;








