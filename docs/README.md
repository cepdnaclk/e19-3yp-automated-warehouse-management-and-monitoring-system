---
layout: home
permalink: index.html

# Please update this with your repository name and project title
repository-name: eYY-3yp-project-template
Project: Automated Warehouse Management and Monitoring System
title: PalletPro 
---

[comment]: # "This is the standard layout for the project, but you can clean this and use your own template"



# PalletPro - Automated Warehouse Management and Monitoring System

---

## Team  
-  E/19/142, Hashini Illangarathne [email](mailto:e19142@eng.pdn.ac.lk)
-  E/19/264, Pawani Nishantha [email](mailto:e19264@eng.pdn.ac.lk)
-  E/19/304, Sajith Priyankara, [email](mailto:e19304@eng.pdn.ac.lk)
-  E/19/363, Nimnadi Senevirathna [email](mailto:e19363@eng.pdn.ac.lk)
-  E/19/375, Dasun Silva [email](mailto:e19375@eng.pdn.ac.lk)


<!-- Image (photo/drawing of the final hardware) should be here -->

<!-- This is a sample image, to show how to add images to your page. To learn more options, please refer [this](https://projects.ce.pdn.ac.lk/docs/faq/how-to-add-an-image/) -->

<!-- ![Sample Image](./images/sample.png) -->

## Table of Contents
1. [Introduction](#introduction)
2. [Solution Architecture](#solution-architecture )
3. [Hardware & Software Designs](#hardware-and-software-designs)
4. [Testing](#testing)
5. [Detailed budget](#detailed-budget)
6. [Conclusion](#conclusion)
7. [Links](#links)

## Introduction

### About

The world of logistics and warehousing has seen a significant transformation with the integration of automation and robotics. In particular, the use of automated pallet jacks has become increasingly vital for efficient material handling within warehouses, distribution centers, and manufacturing facilities. These automated systems streamline operations by reducing manual labor, enhancing productivity, and ensuring safer working environments.<br><br>
Our project focuses on the design, development, and implementation of an advanced automated pallet jack system. The primary objective is to create a robust, intelligent, and adaptable pallet jack that can autonomously navigate through warehouse environments, pick up, transport, and drop off pallets with precision and efficiency. Incorporating cutting-edge technology and innovative engineering, this project aims to revolutionize material handling processes, contributing to increased operational efficiency and reduced labor costs for businesses.<br>

<p align ="center">


https://github.com/cepdnaclk/e19-3yp-automated-warehouse-management-and-monitoring-system/assets/115541700/dd2e6886-6607-43b6-a39d-fb8224b15fe3


</p><br>

### Challenges of current system
- Without automated pallet jacks, workers have to do more physical work, which can be tiring and take longer.

- Workers might spend time on simple tasks instead of doing more important jobs that need thinking.

- If a warehouse gets busier, it's harder to handle more goods without hiring lots more people.

- When people move things manually, there might be mistakes or things might not be done the same way each time.

- Moving heavy things can be risky for workers. Even with safety rules, accidents might still happen.

- Proper training for manual pallet jack operation requires time and resources, impacting operational timelines.

- Manual operations might have limitations in speed and efficiency, affecting overall productivity and throughput rates.<br><br>

### Advantages of our system
- Automated pallet jacks work faster and more consistently than manual ones, improving the speed of moving goods from one place to another.

- They decrease the need for human workers to physically move items, freeing up labor for more complex or critical tasks.

- Automated systems are more precise in handling goods, reducing errors and ensuring items are placed or moved accurately.

- They minimize the risk of workplace injuries by reducing manual lifting and handling of heavy items.

- Automated pallet jacks can handle a higher volume of goods in a shorter time, improving overall warehouse productivity.

- Many automated systems can adapt to changes in the warehouse environment or workload, providing flexibility in operations.

- They can be integrated with other systems, such as inventory management or tracking, streamlining warehouse processes and enhancing accuracy.

- Automated pallet jacks can work continuously without breaks, enabling operations to continue around the clock.

- While there's an initial investment, automated systems can lead to long-term cost savings by reducing labor expenses and improving operational efficiency.<br><br>


  
## Solution Architecture
### High level diagram 
<p align ="center">
     ![Capture1](https://github.com/cepdnaclk/e19-3yp-automated-warehouse-management-and-monitoring-system/assets/115541700/b5db2601-4038-46c2-ae86-30d9637026b5)
</p><br>

The high-level solution architecture for the automated pallet jack comprises three key components.

Ultrasonic Sensors:
- Purpose: Enable obstacle avoidance and mapping.
- Functionality: Emit ultrasonic waves to detect obstacles and map the environment for safe and efficient navigation.
  
Weight Sensors:
- Purpose: Accurately measure the weight loaded onto the pallet jack.
- Functionality: Continuously monitor load weight in real-time, ensuring optimal capacity for safe and efficient material transportation.
  
WiFi Module:
- Purpose: Facilitate precise location tracking.
- Functionality: Scan WiFi beacons and measure signal strength to determine the pallet jack's location, enhancing navigation accuracy.<br><br>

## Hardware and Software Designs
### Hardware Design
<p align ="center">
     ![Capture2](https://github.com/cepdnaclk/e19-3yp-automated-warehouse-management-and-monitoring-system/assets/115541700/72ecb899-6e0d-44af-89fb-495f9a60efbe)
</p><br>



## Testing

Testing done on hardware and software, detailed + summarized results

## Detailed budget


| Item          | Quantity  | Unit Cost  | Total  |
| ------------- |:---------:|:----------:|-------:|
| ESP32 - Wifi Module   | 1         | 1500 LKR     | 1500 LKR |
| ESP8266 - Wifi Module   | 6         | 700 LKR     | 4200 LKR |
| L298N Motor Driver   | 2         | 430 LKR     | 860 LKR |
| HC-SR04 Ultrasonic Sensor   | 2        | 250 LKR     | 500 LKR |
| Strin Gauge   | 1         | 400 LKR     | 400 LKR |
| Motors   | 2         | 4000 LKR     | 8000 LKR |
| Wheels   | 4         | 1500 LKR     | 6000 LKR |
| KY003 Hall Effect Sensors   | 3         | 170 LKR     | 510 LKR |
| Other Non-Electronic Material   | 1         | 5000 LKR     | 5000 LKR |

## Conclusion

What was achieved, future developments, commercialization plans

## Links

- [Project Repository](https://github.com/cepdnaclk/{{ page.repository-name }}){:target="_blank"}
- [Project Page](https://cepdnaclk.github.io/{{ page.repository-name}}){:target="_blank"}
- [Department of Computer Engineering](http://www.ce.pdn.ac.lk/)
- [University of Peradeniya](https://eng.pdn.ac.lk/)

[//]: # (Please refer this to learn more about Markdown syntax)
[//]: # (https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)
