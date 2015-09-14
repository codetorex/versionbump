
# Readme

versionbump is cli tool for managing software version

Create a version_config.json file

```
{
    "projects": {
        "versionbump": {
            "version": {
                "build": 18,
                "major": 1,
                "minor": 0,
                "version": "{major}.{minor} build {build} {suffix}",
                "version_file": "{major}.{minor}-{build}{suffix}",
                "suffix": "beta",
                "outputs": [
                    {
                        "template": "version.template.js",
                        "output": "./lib/version.js"
                    }
                ]
            }
        }
    }
}
```

*Usage:*
```
Usage: node versionbump.js

  -c, --config=ARG  set config file name
  -b, --bump=ARG    bump values "build,major,minor"
  -a, --amount=ARG  bump amount (default:1)
  -g, --get=ARG     get values "build,major,minor,version"
  -h, --help        display this help
  -v, --version     show version
```

*Examples:*

To increase value of 'build' in 'versionbump' project
```
versionbump -b versionbump.version.build
```

To get current version to use in bash scripts:
```
versionbump -g versionbump.version.version
```

You can use any values instead of "build", "major", "minor".
You can use any of these variables as templates.

Example js template:
```
exports.Build = "{build}";
exports.Major = "{major}";
exports.Minor = "{minor}";
exports.Version = exports.Major + "." + exports.Minor;
```

If template path is starts with ./ it will resolve to working directory scope.
If it doesnt starts with that, it will use predefined template.

Current predefined templates:
* javascript - version.template.js


## License 

(The MIT License)

Copyright (c) 2015-2016 Burak Y. &lt;627572616b@gmail.com&gt;

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
