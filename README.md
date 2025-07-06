# Arts_Management_System

The **Arts Management System** is a user-friendly software platform to help museums and galleries efficiently catalog, manage, and organize their artwork collections. Built with **C++** for data processing, **PhpMyAdmin** (served with XAMPP) for the database observation, and **MySQL** for robust data storage, this system enables curators and staff to store, retrieve, and update information about artworks, artists, and exhibitions.

---

## Features

- Add, edit, and delete artwork records  
- Store detailed metadata (artist, year, category, description, etc.)  
- Search and filter artworks by multiple attributes  
- Manage artist profiles and exhibition details  
- MySQL database for secure, persistent storage   
- C++ scripts for advanced data analysis or reporting  
- Clean, menu-driven design for ease of use  

---

## Tech Stack

- **C++** – backend scripts for reports and data processing   
- **MySQL** – relational database (set up via MySQL Installer)
- **PHP**(XAMPP) - connection of backend and frontend

---

##  Database Schema

- **artworks** table: stores artwork details  
- **artists** table: holds artist profiles  
- **exhibitions** table: manages exhibition/event data  
- relationships between artworks and artists for quick lookup  

---

## Getting Started

1. **Clone the repository**  
   ```bash
   git clone https://github.com/yourusername/art-management-system.git


2. **Set up the mySQL database** : run schema.sql to create required tables, you can do this via MySQL Workbench or command line

3. **Configure PHP** : Update your config.php to match your MySQL credentials, Place the project folder inside C:\xampp\htdocs\

4. **Start your local server** (XAMPP, Apache, etc.)
   
5. **Connect backend to frontend through php**

6. **Run the code**

