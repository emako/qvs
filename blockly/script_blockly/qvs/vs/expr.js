/**
 * Generate js representing the specified code input for std.Expr.
 * See more: http://www.vapoursynth.com/doc/functions/expr.html
 * @param {string} expr The expression, expr, is written using reverse polish notation.
 * @return {string} Generated code.
 */
var convertExpr = function(expr) {
    // Clip load operators: x-z, a-w
    var variables = [];
    for (var i = 97; i < 123; i++) {
        variables.push(String.fromCharCode(i));
    }

    // The operators taking one argument are: exp log sqrt abs not dup dupN
    var operators1 = ["exp", "log", "sqrt", "abs", "not", "dup", "dupN"];

    // The operators taking two arguments are: + - * / max min pow > < = >= <= and or xor swap swapN
    var operators2 = ["+", "-", "*", "/", "max", "min", "pow", ">", "<", "=", ">=", "<=", "and", "or", "xor", "swap", "swapN"];

    // The operators taking three arguments are: ?
    var operators3 = ["?"];

    var findTarget = (inputRpns, targets) => {
        for (var i = 0; i < inputRpns.length; i++) {
            for (var j = 0; j < targets.length; j++) {
                if (inputRpns[i] == targets[j]) {
                    return i;
                }
            }
        }
        return null;
    };

    // convert from reverse polish notation
    var convertRpn = function (rpn) {
        var rpns = rpn.split(" ");

        for (;;) {
            var o1 = findTarget(rpns, operators1);
            var o2 = findTarget(rpns, operators2);
            var o3 = findTarget(rpns, operators3);
            var os = [];
            if (o1 != null) {
                os.push(o1);
            }
            if (o2 != null) {
                os.push(o2);
            }
            if (o3 != null) {
                os.push(o3);
            }
            
            var ot = "";
            if (os.length > 0) {
                var oi = Math.min.apply(null, os);
                if (oi == o1) {
                    ot = "1";
                }
                else if (oi == o2) {
                    ot = "2";
                }
                else if (oi == o3) {
                    ot = "3";
                }
                switch (ot) {
                    case "1":
                        var v = "";
                        var o = rpns[oi];
                        var v1 = rpns[oi - 1];
                        switch (o) {
                            case "not":
                                v = o + "!" + v1;
                                break;
                            default:
                                v = o + "(" + v1 + ")";
                                break;
                        }
                        rpns.splice(oi - 1, 2, v);
                        break;
                    case "2":
                        var v = "";
                        var o = rpns[oi];
                        var v1 = rpns[oi - 2];
                        var v2 = rpns[oi - 1];
                        switch (o) {
                            case "+":
                            case "-":
                            case "*":
                            case "/":
                            case ">":
                            case "<":
                            case "=":
                            case ">=":
                            case "<=":
                            default:
                                v = "(" + v1 + " " + o + " " + v2 + ")";
                                break;
                            case "and":
                                v = "(" + v1 + " && " + v2 + ")";
                                break;
                            case "or":
                                v = "(" + v1 + " || " + v2 + ")";
                                break;
                            case "xor":
                                v = "(" + v1 + " ^ " + v2 + ")";
                                break;
                            case "max":
                            case "min":
                            case "pow":
                            case "swap":
                            case "swapN":
                                v = o + "(" + v1 + ", " + v2 + ")";
                                break;
                        }
                        rpns.splice(oi - 2, 3, v);
                        break;
                    case "3":
                        var v = "";
                        var o = rpns[oi];
                        var v1 = rpns[oi - 3];
                        var v2 = rpns[oi - 2];
                        var v3 = rpns[oi - 1];
                        switch (o) {
                            case "?":
                                v = "(" + v1  + " " + o + " " + v2 + " : " + v3 + ")";
                                break;
                        }
                        rpns.splice(oi - 3, 4, v);
                        break;
                }
            }
            else {
                break;
            }
        }
        return rpns;
    }

    return convertRpn(expr);
};

/**
 * Calc the specified code for test std.Expr.
 * See more: http://www.vapoursynth.com/doc/functions/expr.html
 * @param {string} expr The expression, expr, is written using reverse polish notation.
 * @param {json} param The expression params.
 * @param {float} limit The calc result limit. Like 255, 65535 or null for the result of the expression is stored without any clamping.
 * @return {float} Calc result.
 */
var calcExpr = function(expr, param, limit = null) {
    var operatorExpr = "";
    for (operator in ["max", "min", "pow", "exp", "log", "sqrt", "abs"]) {
        operatorExpr += "var " + operator + " = Math." + operator + ";\n";
    }
    operatorExpr += `function swap(a, b) { var tmp = a; this.a = b; this.b = tmp; };`;
    operatorExpr += `function swapN(a, b) { var tmp = a; this.a = b; this.b = tmp; };`;
    operatorExpr += `function dup(a) { return a; };`;
    operatorExpr += `function dupN(a) { return a; };`;
    var paramExpr = "";
    for (prop in param) {
        paramExpr += "var " + prop + " = " + param[prop] + ";\n";
    }
    var realExpr = convertExpr(expr);
    var finallExpr = operatorExpr + paramExpr + realExpr;
    var result = eval(finallExpr);

    if (result != null && result != undefined) {
        if (result > limit) {
            result = limit;
        }
    }
    if (result < 0) {
        result = 0;
    }
    return result;
};

// Examples1
// var expr1 = convertExpr("1 3 5 * + 7 9 / -");
// var result1 = calcExpr("1 3 x * + 7 9 / -", {
//     x: 5,
// });

// Examples2
// var expr2 = convertExpr("x y 64 * + z 256 * + 3 /");
// var result2 = calcExpr("x y 64 * + z 256 * + 3 /", {
//     x: 13,
//     y: 6,
//     z: 230,
// }, 65535);
