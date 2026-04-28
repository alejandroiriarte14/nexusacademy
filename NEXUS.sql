CREATE DATABASE IF NOT EXISTS sistema;
USE sistema;

DROP TABLE IF EXISTS alumnos;

CREATE TABLE alumnos (
    id INT PRIMARY KEY,
    nombre VARCHAR(50),
    apellido VARCHAR(50),
    celular VARCHAR(20),
    nota_final DECIMAL(4,2),
    estado VARCHAR(20)
);

INSERT INTO alumnos VALUES
(1001,'Ignacio','Franichevich','76543210',9.70,'Aprobado'),
(1002,'Alejandro','Iriarte','71234567',9.60,'Aprobado'),
(1003,'Nadya','Saric','73456789',9.50,'Aprobado'),
(1004,'Martina','Lopez','74561234',7.40,'Aprobado'),
(1005,'Regina','Cortez','75678901',6.90,'Aprobado'),
(1006,'Leandro','Martinez','76789012',5.30,'Aprobado'),
(1007,'Jose','Reyes','77890123',8.10,'Aprobado'),
(1008,'Camila','Vargas','78901234',3.50,'Reprobado'),
(1009,'Lucia','Flores','79012345',10.00,'Aprobado'),
(1010,'Pedro','Suarez','70123456',2.80,'Reprobado'),
(1011,'Valeria','Ruiz','72223344',8.90,'Aprobado'),
(1012,'Mateo','Castro','73334455',6.10,'Aprobado'),
(1013,'Fernanda','Navarro','74445566',3.20,'Reprobado'),
(1014,'Kevin','Salazar','75556677',7.20,'Aprobado'),
(1015,'Paula','Mendoza','76667788',3.00,'Reprobado');
