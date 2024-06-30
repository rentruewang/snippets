#Contributing

## Code style

1. Use ISO Cpp's code style (`snake_case_everything`).
2. Except for private member variable, (`suffix_with_underscore_`).
3. Use `clang-format` (`BasedOnStyle: Chromium; IndentWidth: 4`).
4. Use `=` initialization only for pointer / reference types.
5. Use `{}` universal initialization for everything else.
6. Except when ambiguous, then use `()` normal initialization.
7. Never omit braces after `if` / `else` / `while` / `for`.
8. Except for side effects (empty body). In which case put a `;` as the body.
9. Use `///` for documentation strings.
10. Follow [CppCoreGuidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).
