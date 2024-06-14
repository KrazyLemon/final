CREATE TABLE Datos (
    id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    temp FLOAT(10,2),
    hum FLOAT(10,2),
    heat FLOAT(10,2),
    smp_a INT(6),
    smp_b INT(6),
    smp_c INT(6),
    smp_d INT(6),
    smp_e INT(6),
    posted_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

CREATE TABLE Outputs (
    id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(64),
    board INT(6),
    gpio INT(6),
    state INT(6)
);

CREATE TABLE Boards (
    id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    board INT(6),
    last_request TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

CREATE TABLE Users(
    id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255),
    email VARCHAR(255),
    password VARCHAR(255) 
);

INSERT INTO `Boards`(`board`) VALUES (1);
INSERT INTO `Users` VALUES(1,'ADMON','admon@verdetech.com','12345678');
INSERT INTO `Outputs`(`name`, `board`, `gpio`, `state`) VALUES ("Built-in LED", 1, 2, 0);
INSERT INTO `Outputs`(`name`, `board`, `gpio`, `state`) VALUES ("Bomba", 1, 17, 1);