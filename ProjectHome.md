# KF-Ray #

**A ray tracing program which can create realistic images and perform parallel computing.**

> "Ray tracing is a technique for generating an image by tracing the path of light through pixels in an image plane. The technique is capable of producing a very high degree of photorealism ; usually higher than that of typical scanline rendering methods, but at a greater computational cost."
**_Wikipedia on ray tracing_**

---

[http://kfray.free.fr/screenshots/17\_small.PNG](http://kfray.free.fr/screenshots/17.png) ![![](http://kfray.free.fr/screenshots/scn5_small.png)](http://kfray.free.fr/screenshots/scn5.png) ![![](http://kfray.free.fr/screenshots/scn6_small.png)](http://kfray.free.fr/screenshots/scn6.png) ![![](http://kfray.free.fr/screenshots/scene7_small.png)](http://kfray.free.fr/screenshots/scene7.png)

---


_KF-Ray_ is a ray tracing program which can perform parallel computing.

_KF-Ray_ is purely written in C and works on an UNIX/Linux system. It can be use with several computers/clusters in the same time for parallel rendering with MPI.

_KF-Ray_ is mostly in French (commentaries, documentation, manual) but the code is entirely in English (variable, function names). Thus, it is still easy to modify.

_KF-Ray_ was developed during our second year engineering school.

You can download the last release in the downloads tab or you can get the very last revision from the subversion repository :<br>
<code>svn checkout "http://kf-ray.googlecode.com/svn/trunk/" kfray</code><br>
<hr />
<b>News for 1.0.2</b> (only available in SVN repository)<br>
<ul><li>Mist effect added<br>
</li><li>Shared-memory parallelism with OpenMP (faster for a multi-core computer)<br>
</li><li>Anti-aliasing with Monte-Carlo method</li></ul>

<b>KF-Ray Features for Release 1.0.1</b>
<ul><li>Effects<br>
<ul><li>Reflections, shadows, refractions (in progress transparency is available)<br>
</li><li>Bump mapping<br>
</li></ul></li><li>Objects<br>
<ul><li>Lights (punctual)<br>
</li><li>Spheres<br>
</li><li>Planes<br>
</li></ul></li><li>Reflectance models<br>
<ul><li>Diffuse (Lambert)<br>
</li><li>Specular (Blinn-Phong)<br>
</li></ul></li><li>Procedural textures<br>
<ul><li>Perlin noise (turbulence, wood, marbel)<br>
</li><li>Checker<br>
</li></ul></li><li>Perspective projection with a right handed coordinate system<br>
</li><li>High Performance Computing<br>
<ul><li>Distribute jobs on clusters with MPI<br>
</li><li>Dynamic Master/Slave Load Balancing<br>
</li></ul></li><li>Need only few libraries<br>
</li><li>Load personalised description files with easy syntax<br>
</li><li>Easy to use with a simple user interface in GTK+<br>
</li><li>Well-documented code easy to read and modify (Doxygen)<br>
</li><li>Can render some 3D animations (in progress)<br>
<hr /></li></ul>

Here a little 3D animation rendered with KF-Ray (watch in HD) :<br>
<br>
<a href='http://www.youtube.com/watch?feature=player_embedded&v=we_XeS_Gv7o' target='_blank'><img src='http://img.youtube.com/vi/we_XeS_Gv7o/0.jpg' width='425' height=344 /></a>