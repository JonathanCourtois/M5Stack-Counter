[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="url"><img src="https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/Images/M5Stack%20Design/optionTrue.png" align="center" height="100" width="100" ></a>
  
  <h3 align="center">M5Stack-Counter</h3>

  <p align="center">
    My first test of the M5Stack.
    This is a little application to use M5Stack as a Passing Doors sensor.
  </p>
</p>
<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
* [How it work](#how-it-work)
* [How to use it](#how-to-use-it)

<!-- ABOUT THE PROJECT -->
## About The Project

This project is extract from one of my courses project : [Mini-projet_compteur](https://github.com/ltombak/Mini-projet_compteur) (host in the [ltombak](https://github.com/ltombak) Github).
The objectif was to create an IOT system to control the peoples number in an aera like shops.
So the M5Stack can be use to measure distance but also as a passing door counter.
(This version is without bluetooth).

<!-- HOW IT WORK-->
## How it work
First of all you need Two ultrasonic sensor to measure the distance.
After you have to but theme to create two beam in each side of the door.
When it's done, if someone pass the door the beans will be interupt. If you know which beam is interupt before the other, you can know the direction so if the person is entering or exiting.
<p align="center">
  <img width="400" src="https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/Images/M5Stack%20Design/passingDoor.png"/>
</p>

<!-- HOW TO USE IT -->
## How to use it
After placing it on a door, you have juste to follow the action buttons names to know what to do.
you can :
- Activate or not the auto area count <br>
  - This action will create a peoples limit, displayed on the counter menu, if a suitable area is entered in the area menu.
<p align="center">
  <img width="200" src="https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/Images/M5Stack%20Design/optionFalse.png"/>
  <img width="200" src="https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/Images/M5Stack%20Design/optionTrue.png"/>
</p>
- Enter in the surface menu<br>
  - This menu allow you to set the area of the shop
<p align="center">
  <img width="200" src="https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/Images/M5Stack%20Design/areaLimit.png"/>
  <img width="200" src="https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/Images/M5Stack%20Design/areaMenu0.png"/>
  <img width="200" src="https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/Images/M5Stack%20Design/areaMenu30.png"/>
</p>
- Enter in the counter menu<br>
  - This menu will display the peoples count. It will display a peoples limit if the auto area is activate. this menu is locked if you activate the area auto count but with a non-suitable area.
<p align="center">
  <img width="200" src="https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/Images/M5Stack%20Design/counter.png"/>
  <img width="200" src="https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/Images/M5Stack%20Design/counterWithoutLimit.png"/>
  <img width="200" src="https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/Images/M5Stack%20Design/counterLimit0.png"/>
  <img width="200" src="https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/Images/M5Stack%20Design/counterLimit3.png"/>
  <img width="200" src="https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/Images/M5Stack%20Design/counterPopup.png"/>
</p>
- Enter in the distance menu<br>
  - This menu will display the distance seen by the sensors
<p align="center">
  <img width="200" src="https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/Images/M5Stack%20Design/distance.png"/>
  <img width="200" src="https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/Images/M5Stack%20Design/distanceMenu.png"/>
  <img width="200" src="https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/Images/M5Stack%20Design/distanceMenuError.png"/>
</p>
<p align="center">
  <img width="500" src="https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/Images/M5Stack%20Design/Orga.png"/>
  <figcaption align="center" ><i>Organization chrat</i></figcaption>
</p> 


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/JonathanCourtois/M5Stack-Counter.svg?style=flat-square
[contributors-url]: https://github.com/JonathanCourtois/M5Stack-Counter/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/JonathanCourtois/M5Stack-Counter.svg?style=flat-square
[forks-url]: https://github.com/JonathanCourtois/M5Stack-Counter/network/members
[stars-shield]: https://img.shields.io/github/stars/JonathanCourtois/M5Stack-Counter.svg?style=flat-square
[stars-url]: https://github.com/JonathanCourtois/M5Stack-Counter/stargazers
[issues-shield]: https://img.shields.io/github/issues/JonathanCourtois/M5Stack-Counter.svg?style=flat-square
[issues-url]: https://github.com/JonathanCourtois/M5Stack-Counter/issues
[license-shield]: https://img.shields.io/github/license/JonathanCourtois/M5Stack-Counter.svg?style=flat-square
[license-url]: https://github.com/JonathanCourtois/M5Stack-Counter/blob/master/LICENSE
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/jonathan-courtois
[product-screenshot]: image/Presentation/FirstBuild.PNG
