/// <reference path="../typings/node/node.d.ts" />

import fs = require('fs');
import path = require('path');

var log = new (require('log'));

var opt = require('node-getopt').create([
    ['c', 'config=ARG', 'set config file name'],
    ['b', 'bump=ARG', 'bump values "build,major,minor"'],
    ['a', 'amount=ARG', 'bump amount (default:1)'],
    ['g', 'get=ARG', 'get values "build,major,minor,version"'],
    /*['s', '', 'short option.'],
     ['', 'long', 'long option.'],
     ['S', 'short-with-arg=ARG', 'option with argument'],
     ['L', 'long-with-arg=ARG', 'long option with argument'],
     ['', 'color[=COLOR]', 'COLOR is optional'],
     ['m', 'multi-with-arg=ARG+', 'multiple option with argument'],
     ['', 'no-comment'],
     ,
     */
    ['h', 'help', 'display this help'],
    ['v', 'version', 'show version']
])              // create Getopt instance
    .bindHelp()     // bind option 'help' to default action
    .parseSystem(); // parse command line


function get_replacement_groups(value: string) {
    var regex = /{([^{}]*)}/g;
    var match: any;
    var result: any[] = [];
    while (match = regex.exec(value)) {
        if (result.indexOf(match[1]) < 0) {
            result.push(match[1]);
        }
    }
    return result;
}

function replaceAll(str, find, replace) {
    return str.split(find).join(replace);
}

function template(t: string, data: any) {
    var replacements = get_replacement_groups(t);
    var result = t;
    for (var i = 0; i < replacements.length; i++) {
        var cur = replacements[i];
        if (!data.hasOwnProperty(cur)) {
            continue;
        }
        result = replaceAll(result, "{" + cur + "}", data[cur]);
    }

    return result;
}

function getversion(data: any, path_str: string) {

    var path = path_str.split('.');

    var cur = data.projects;
    for (var i = 0; i < path.length - 1; i++) {
        cur = cur[path[i]];
    }

    var last = path[path.length - 1];

    if (typeof cur[last] == "string") {
        return template(cur[last], cur);
    }
    else if (typeof cur[last] == "undefined") {
        log.error("Wrong parameter for get ", path);
    }

    return cur[last];
}

function processoutputs(outputs: any[], data: any) {
    for (var i = 0; i < outputs.length; i++) {
        var unresolved_path: string = outputs[i].template;
        var unresolved_output: string = outputs[i].output;

        var template_path;
        if (unresolved_path.substr(0, 2) == './') {
            template_path = path.resolve(unresolved_path);
        }
        else {
            template_path = path.resolve(__dirname, "../templates/", unresolved_path);
        }

        var resolved_output = path.resolve(unresolved_output);

        var fileContent = fs.readFileSync(template_path, 'utf8')
        var processed = template(fileContent, data);
        fs.writeFileSync(resolved_output, process);
    }
}

function navigate(data: any, path: string[]) {
    var cur = data.projects;
    for (var i = 0; i < path.length - 1; i++) {
        cur = cur[path[i]];
    }

    var last = path[path.length - 1];

    return cur[last];
}

function bump(data: any, path: string[], amount: number) {
    amount = parseInt(amount + "");
    var cur = data.projects;
    for (var i = 0; i < path.length - 1; i++) {
        cur = cur[path[i]];
    }

    var last = path[path.length - 1];

    if (typeof cur[last] == "number") {
        log.info("Current value: ", cur[last]);
        cur[last] += amount;
        log.info("Increased to: ", cur[last]);

        return true;
    }
    else if (typeof cur[last] == "undefined") {
        log.error("Wrong parameter for bump ", path);
        return false;
    }

    return false;
}

export function main() {
    if (opt.options.version) {
        console.info(opt);
        console.info("v1.0");
    }


    var configName = opt.options.config || "version_config.json";

    if (typeof opt.options.get != "undefined") {
        log.level = log.EMERGENCY;
    }

    log.info("Loading: ", configName);

    var config_path = path.resolve("./", configName);

    var settings = JSON.parse(fs.readFileSync(config_path, 'utf8'));

    //console.info("Config: ", settings);

    if (opt.options.hasOwnProperty('bump')) {

        var path_str = opt.options.bump;
        var path_arry: string[] = path_str.split('.');
        var amount = opt.options.amount || 1;

        log.info("Bumping: ", path_str);
        bump(settings, path_arry, amount);

        fs.writeFileSync(config_path, JSON.stringify(settings, null, 4));

        var outputPath = path_arry.slice(0, -1);
        var data = navigate(settings, outputPath);
        var outputs = data.outputs;
        if (typeof outputs != "undefined") {
            processoutputs(outputs, data);
        }
    }

    if (opt.options.hasOwnProperty('get')) {
        console.info(getversion(settings, opt.options.get));
    }


}