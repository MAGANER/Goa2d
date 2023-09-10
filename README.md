<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->


<!--
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]
-->


 
<div align="center">
 <!-- 
   PROJECT LOGO
  <a href="https://github.com/othneildrew/Best-README-Template">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>
-->
  <h3 align="center">Goat2D</h3>
  <p>
    Game framework written in C++.
  </p>
    <a href="https://github.com/MAGANER/Goat2d/issues">Report Bug</a>
    <br>
    <a href="https://github.com/MAGANER/Goat2d/issues">Request Feature</a>
  
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

<!-- [![Product Name Screen Shot][product-screenshot]](https://example.com) -->
<p align="center">
I started this framework because of realisation that SFML is not enough to write a game, because you need architecture.
That's the only one reason i deicided to write this framework, also i think there is only one user - me. I write it mainly for my own purposes,
it would be a pleasure to find someone else who finds this project useful for game development.
</p>
<br>
<p>
This framework is made of 2 parts: core and framework itself. These parts are namepspaces actually and they contains really different things.
Core is just an overwrapper of SDL libraries, but Framework contains all classes related to game architecture( or my vision of architecture).
</p>

### Built With
- ```SDL2```
- ```SDL_TTF```
- ```SDL_IMG```

### Projects that used Goat2d
- <a href="https://github.com/MAGANER/Goat2d">Colored 2048</a>

<!-- GETTING STARTED -->
## Getting Started
### Installation

<h4>On your own</h4>
<p>
To build framework on your own, you need to get SDL2 and additional libraries for images, ttf, audio if you use them.
To get all information about these libraries follow <a href="https://www.libsdl.org/">SDL2's official site</a>. Or you 
can follow <a href="https://www.lazyfoo.net/tutorials/SDL/index.php">Lazy Foo's tutorials</a> to find out how to build all required libraries.
After SDL2 and all related libraries are build you should correctly link them to your project with Goat2d or you can statically build goat2d with
all libraries.
</p>

<!-- USAGE EXAMPLES 
### Usage
<h4 align="center">Creation of window</h4>
```c++

```-->

<!-- ROADMAP -->
## Versions and related features
Note: i can add new features to next version's list as time goes by.

### Version 0.1(current)
- [x] Creation of basic window without icon and ability to resize dynamicly and without ability to set Fullscreen
- [x] Ability to render basic primitive shapes: Rectangles, Points, Lines
- [x] Ability to load and render images in form of textures(for available image formats, check out SDL_IMG official site)
- [x] Ability to load TTF fonts and render texts
- [x] Ability to process keyboard events
- [x] Set of basic classes to implement Scenes, Events
- [x] Added doxygene generated documentation
- [ ] CMake list
- [ ] automated script to configure framework  

### Version 0.2
- [] Creation of fully customized window with icons, dynamic resiing and fullscreen
- [] mouse events support
- [] audio processing
- [] sprite tileset processing

<!-- CONTRIBUTING 
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>

-->

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<!-- CONTACT -->
## Contact

Ian(mainteiner) - haskel.lisp@yandex.ru

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments
* [My thoughts on the game architecture - overview on this framework's philosophy](https://maganer.github.io/HaskelLispPlace/articles/game_architecture)
