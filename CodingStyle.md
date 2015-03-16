

# Basic Rules #

Imposed by our tutor

  * Function bodies MUST NOT contain more than 25 lines, enclosing braces and assert() excluded.
  * Lines MUST NOT exceed 80 characters in width, including the trailing newline character.
  * All functions MUST be commented with Doxygen in header files :
```
/**
 * \fn 		t_vector	Normalize(t_vector v);
 * \brief 	Normalize a vector
 *
 * \param 	v vector
 * \return      Normalized vector
 */
t_vector	Normalize(t_vector v);
```
  * Global variable names are PROHIBITED
  * Header files MUST be protected against multiple inclusion. The protection “key” MUST be the name of the file, entirely capitalized, which punctuation replaced with underscores, and an additional underscore appended. For example, if the file name is foo.h, the protection key SHALL be ‘FOO\_H\_’:
```
#ifndef FOO_H_
# define FOO_H_
/*
** Contents of foo.h
*/
#endif /* !FOO_H_ */
```
  * The code MUST be indented and follow the BSD/Allman or ANSI style.
  * Repertories MUST be used and organize the whole code.
  * Entities (variables, functions, macros, types, files or directories) SHOULD have explicit and/or mnemonic names.

For more precise rules, we can consult [Epita Coding Style Standard](http://www.lrde.epita.fr/~raph/docs/epita-css/codingstyle.pdf)


# Our choices #

  * KF-Ray is developped with `CodeBlocks` 8.02. A GUI and backend Codeblocks projects are available in the source.
  * We use Tab character and indents with a 8 size space in order to make it viewable under Emacs and VI.