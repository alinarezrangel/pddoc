# pddoc
<<<<<<< HEAD

El documentador oficial de PseudoD

# Descripción
`pddoc` es una herramienta de uso sencillo, completamente personalizable
que genera código HTML5 en base a los comentarios de un programa en
[PseudoD](https://github.com/alinarezrangel/PseudoD "Pagina en GitHub de PseudoD").

La salida es totalmente personalizable por medio de CSS, y permite el uso de
JavaScript.

# Sintaxis
La sintaxis del archivo de entrada corresponde con la sintaxis de PseudoD
v2.1.0. `pddoc` simplemente detectara los comentarios que comienzen por
`[DOCUMENTA` y terminen por `DOCUMENTA]`, sus etiquetas estan basadas en
[Doxygen](http://www.stack.nl/~dimitri/doxygen/).
=======
El documentador oficial de PseudoD
# Descripción
`pddoc` es una herramienta de uso sencillo, completamente personalizable que genera código HTML5 en base a los comentarios de un programa en [PseudoD](https://github.com/alinarezrangel/PseudoD "Pagina en GitHub de PseudoD").

La salida es totalmente personalizable por medio de CSS, y permite el uso de JavaScript.
# Sintaxis
La sintaxis del archivo de entrada corresponde con la sintaxis de PseudoD u1.9.5. `pddoc` simplemente detectara los comentarios que comienzen por `[DOCUMENTA` y terminen por `DOCUMENTA]`, sus etiquetas estan basadas en [Doxygen](http://www.stack.nl/~dimitri/doxygen/).
>>>>>>> 7ec3710b332a74f0f40f262e20e29c20e6cfc959

Un ejemplo de código sería:

```
[DOCUMENTA
@brief Es el "Hola Mundo".
Es el típico programa Hola Mundo, solo que
en una función.
@arg pers Persona a la cual saludar, si es NULO o no se especifica, se reemplaza por "Mundo".
@dev Siempre devuelve VERDADERO.
@errors Active
DOCUMENTA]
funcion HolaMundo
  ...
finfun
```

<<<<<<< HEAD
Un ejemplo de pagina generada por `pddoc`, es la
[documentación oficial](http://pseudod.sourceforge.net/bepd_index.html) de
la biblioteca estándar de PseudoD.

# Uso

=======
Un ejemplo de pagina generada por `pddoc`, es la [documentación oficial](http://pseudod.sourceforge.net/bepd_index.html) de la biblioteca estándar de PseudoD.
# Uso
>>>>>>> 7ec3710b332a74f0f40f262e20e29c20e6cfc959
`pddoc (--css|--head1|--head2|--foot|--help|entrada) [(salida) (estilo) (head1) (head2) (foot) [(--nofoot)]]`
