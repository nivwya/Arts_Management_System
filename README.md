# Arts_Management_System

The **Arts Management System** is a user-friendly software platform to help museums and galleries efficiently catalog, manage, and organize their artwork collections. Built with **Python** for backend logic, **PHP** for the web interface, and **Oracle SQL** for robust data storage, this system enables curators and staff to store, retrieve, and update information about artworks, artists, and exhibitions.

---

## Features

- Add, edit, and delete artwork records
- Store detailed metadata (artist, year, category, description, etc.)
- Search and filter artworks by multiple attributes
- Manage artist information and exhibition details
- Oracle SQL database for secure, persistent storage
- Intuitive PHP-based web interface
- Clean, menu-driven design for easy operation

---

## Tech Stack

- **Python** – backend scripts for data handling and reports  
- **PHP** – user-facing web interface  
- **Oracle SQL** – relational database  
- **HTML / CSS / JavaScript** – for responsive user experience

---

## Database Schema

- **artworks** table: stores each artwork’s details  
- **artists** table: holds artist profiles  
- **exhibitions** table: manages exhibition and event data  
- relationships between artworks and artists for fast lookup

---

## Getting Started

1. **Clone the repository**  
   ```bash
   git clone https://github.com/yourusername/art-management-system.git

2. **Set up the Oracle SQL database** : run schema.sql to create required tables

3. **Configure PHP** : adjust database connection settings in config.php to match your Oracle credentials

4. **Start your local server** (XAMPP, Apache, etc.)

5. **Run the application**
    ```bash
    http://localhost/art-management-system

