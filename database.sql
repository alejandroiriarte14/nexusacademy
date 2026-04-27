CREATE DATABASE IF NOT EXISTS nexus_academy;
USE nexus_academy;

CREATE TABLE IF NOT EXISTS alumnos (
    id INT PRIMARY KEY,
    nombre VARCHAR(50) NOT NULL,
    apellido VARCHAR(50) NOT NULL,
    celular VARCHAR(20),
    nota_final DECIMAL(4,2),
    estado VARCHAR(20) GENERATED ALWAYS AS (
        CASE 
            WHEN nota_final >= 4 THEN 'Aprobado' 
            ELSE 'Reprobado' 
        END
    ) STORED
);

-- 3. Carga de Datos (15 Alumnos de ejemplo)
INSERT INTO alumnos (id, nombre, apellido, celular, nota_final) VALUES
(101, 'Juan', 'Alvarez', '11223344', 6.50),
(102, 'Ana', 'Barrientos', '11667788', 3.00),
(103, 'Edgar', 'Camacho', '11334455', 7.00),
(104, 'Sofía', 'Fernandez', '11332277', 7.50),
(105, 'Ignacio', 'Franichevich', '11228844', 10.00),
(106, 'Francisco', 'Herrera', '11445599', 6.50),  
(107, 'Alejandro', 'Iriarte', '11447799', 9.50),
(108, 'Javier', 'López', '11226688', 2.00),
(109, 'Nicolás', 'Martínez', '11336644', 8.00),
(110, 'Catalina', 'Pizarro', '11558822', 9.80),
(111, 'Luis', 'Puyal', '11662233', 9.60),
(112, 'Mateo', 'Ruiz', '11442288', 8.00),
(113, 'Nadya', 'Saric', '11779988', 9.90),
(114, 'Sebastían', 'Tejada', '11772255', 9.70),
(115, 'José', 'Vega', '11883366', 3.50);

/* COMANDOS DE VERIFICACION:
  
  -- Ranking Top 5:
  SELECT * FROM alumnos ORDER BY nota_final DESC LIMIT 5;
  
  -- Alumnos en riesgo:
  SELECT * FROM alumnos WHERE nota_final < 4;
  
  -- Buscar por ID (ejemplo 105):
  SELECT * FROM alumnos WHERE id = 105;
*/