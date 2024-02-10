//===============================================
// functions
//===============================================
function sprintf() {
    var args = arguments,
    string = args[0],
    i = 1;
    return string.replace(/%((%)|s|d)/g, function (m) {
        // m is the matched format, e.g. %s, %d
        var val = null;
        if (m[2]) {
            val = m[2];
        } else {
            val = args[i];
            // A switch statement so that the formatter can be extended. Default is %s
            switch (m) {
                case '%d': {
                    val = parseFloat(val);
                    if (isNaN(val)) {
                        val = 0;
                    }
                    break;
                }
            }
            i++;
        }
        return val;
    });
}
//===============================================
// base64
//===============================================
function utf8_to_b64(_data) {
    return encodeURIComponent(btoa(_data));
}
//===============================================
function b64_to_utf8(_data) {
    return atob(decodeURIComponent(_data));
}
//===============================================
// xml
//===============================================
String.prototype.toXml = function() {
    var xml = this;
    var tab = "  ";
    var formatted = '', indent= '';
    tab = tab || '\t';
    xml.split(/>\s*</).forEach(function(node) {
        if (node.match( /^\/\w/ )) indent = indent.substring(tab.length); // decrease indent by one 'tab'
        formatted += indent + '<' + node + '>\r\n';
        if (node.match( /^<?\w[^>]*[^\/]$/ )) indent += tab;              // increase indent
    });
    return formatted.substring(1, formatted.length-3);
}
//===============================================
// string
//===============================================
String.prototype.toBase64 = function() {
    var lData = this;
    lData = btoa(lData);
    lData = encodeURIComponent(lData);
    return lData;
}
//===============================================
String.prototype.fromBase64 = function() {
    var lData = this;
    lData = decodeURIComponent(lData);
    lData = atob(lData);
    return lData;
}
//===============================================
