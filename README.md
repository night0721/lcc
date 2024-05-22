# lcc
Lines of Code Counter

# Usage
```sh
lcc <path> <path2> <path3> ...
```

# Dependencies
None

# Building
You will need to run these with elevated privilages.

```
$ make 
# make install
```

# Customizing
You can modify `lcc.h` to add more languages to count lines, with the same format as provided in the file.

You can also add directories name and file extensions to ignore when counting lines, but the length of `ignore_dir` must be matching `IGNORE_DIRS`.

# Warning
Result may not be 100% correct due to coding style, but from testing, code with [suckless coding style](https://suckless.org/coding_style) will be most accurate due to different method of commenting in code.

# Contributions
Contributions are welcomed, feel free to open a pull request.

# License
This project is licensed under the GNU Public License v3.0. See [LICENSE](https://github.com/night0721/lcc/blob/master/LICENSE) for more information.
