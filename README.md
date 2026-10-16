<img width="586" height="358" alt="Screenshot 2026-10-16 213711" src="https://github.com/user-attachments/assets/b5dc0143-860a-436b-9f39-b3124f74ae9c" />
<img width="614" height="377" alt="Screenshot 2026-10-16 213814" src="https://github.com/user-attachments/assets/c77d2967-09a8-4f8f-934d-63f44830d0b1" />
<img width="1536" height="1024" alt="Embedded Linux Network Monitor Architecture" src="https://github.com/user-attachments/assets/35d7286d-77a1-46a2-9e66-93ce97663000" />
#  Embedded Network Monitoring System using Buildroot and QEMU

A lightweight **Embedded Linux Network Monitoring System** developed using **Buildroot** and executed on the **QEMU ARM Emulator**. The application provides a real-time terminal dashboard using the **ncurses** library to monitor important system and network resources.

---

##  Project Overview

This project demonstrates how to build a custom Embedded Linux distribution using **Buildroot**, integrate a custom C application as a Buildroot package, and execute it on a virtual ARM platform using **QEMU**.

The monitoring application displays live system information through an ncurses-based dashboard.

---

##  Features

- Real-time CPU Usage Monitoring
-  Memory Usage Monitoring
-  Disk Usage Monitoring
-  Network Interface Information
-  Internet Connectivity Detection
-  RX/TX Network Traffic Monitoring
-  Running Process Monitoring
-  Event Logging
-  System Health Alerts
-  Interactive ncurses Dashboard

---

##  Technologies Used

- Embedded Linux
- Buildroot 2025.02.5
- QEMU ARM Emulator
- C Programming
- GNU Make
- BusyBox
- ncurses Library
- Linux /proc Filesystem
- Socket Programming

---

##  Project Structure

```
network_monitor/
│
├── include/
│   ├── cpu.h
│   ├── memory.h
│   ├── disk.h
│   ├── interface.h
│   ├── connectivity.h
│   ├── traffic.h
│   ├── process.h
│   ├── config.h
│   └── logger.h
│
├── src/
│   ├── main.c
│   ├── cpu.c
│   ├── memory.c
│   ├── disk.c
│   ├── interface.c
│   ├── connectivity.c
│   ├── traffic.c
│   ├── process.c
│   ├── config.c
│   └── logger.c
│
├── Config.in
├── network_monitor.mk
├── Makefile
└── README.md
```

---

## System Architecture

```
                Buildroot
                    │
                    ▼
        Custom Embedded Linux Image
                    │
                    ▼
              QEMU ARM Emulator
                    │
                    ▼
       Network Monitoring Application
                    │
     ┌──────────────┼──────────────┐
     │              │              │
     ▼              ▼              ▼
CPU Monitor    Memory Monitor   Disk Monitor

     ▼              ▼              ▼

Network Interface ─ Connectivity ─ Traffic

                    │
                    ▼
            ncurses Dashboard
```

---

##  Dashboard Monitors

The application continuously monitors:

- CPU Usage
- Memory Usage
- Disk Usage
- Network Interface
- IP Address
- MAC Address
- Internet Connectivity
- Upload Speed
- Download Speed
- Running Processes
- System Alerts

---

##  Build Process

### Configure Buildroot

```bash
make qemu_arm_vexpress_defconfig
```

### Build the Embedded Linux Image

```bash
make
```

### Start QEMU

```bash
cd output/images
./start-qemu.sh
```

Login

```
root
```

Run

```bash
network_monitor
```

---

## Buildroot Package Integration

The application is integrated as a custom Buildroot package using:

- Config.in
- network_monitor.mk
- Makefile

It is automatically installed into

```
/usr/bin/network_monitor
```

---

##  Configuration

The application reads runtime parameters from

```
/etc/network_monitor.conf
```

Example

```text
REFRESH_TIME=2
CPU_ALERT=80
MEMORY_ALERT=85
DISK_ALERT=90
```

---

##  Modules

| Module | Description |
|---------|-------------|
| main.c | Dashboard Controller |
| cpu.c | CPU Usage Monitor |
| memory.c | Memory Monitor |
| disk.c | Disk Usage Monitor |
| interface.c | Network Interface Information |
| connectivity.c | Internet Connectivity Check |
| traffic.c | Network Traffic Monitor |
| process.c | Running Processes |
| config.c | Configuration Loader |
| logger.c | Event Logger |

---

##  Sample Output

### Internet Connected

- CPU Usage
- Memory Usage
- Disk Usage
- Connected Status
- Network Speed
- Running Processes

### Internet Disconnected

- Connection Status changes to **DISCONNECTED**
- RX/TX Speed becomes **0 KB/s**
- Alert displayed on dashboard

---

##  Learning Outcomes

- Embedded Linux Development
- Buildroot Package Creation
- Linux System Programming
- ncurses Programming
- Socket Programming
- Linux /proc Filesystem
- QEMU ARM Emulation
- Cross Compilation

---

##  Future Enhancements

- Web Dashboard
- Email Alerts
- SNMP Monitoring
- Remote Monitoring
- Log Export
- Performance Graphs
- Multi-interface Support

---
