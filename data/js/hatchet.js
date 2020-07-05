/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2011,      Dominik Schmidt <domme@tomahawk-player.org>
 *   Copyright 2011-2012, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2011,      Thierry Goeckel
 *   Copyright 2013,      Teo Mrnjavac <teo@kde.org>
 *   Copyright 2013-2014, Uwe L. Korn <uwelk@xhochy.com>
 *   Copyright 2014,      Enno Gottschalk <mrmaffen@googlemail.com>
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 */

// if run in phantomjs add fake Hatchet environment
if ((typeof Hatchet === "undefined") || (Hatchet === null)) {
    var Hatchet = {
        fakeEnv: function () {
            return true;
        },
        resolverData: function () {
            return {
                scriptPath: function () {
                    return "/home/hatchet/resolver.js";
                }
            };
        },
        log: function () {
            console.log.apply(arguments);
        }
    };
}

Hatchet.apiVersion = "0.2.2";

//Statuses considered a success for HTTP request
var httpSuccessStatuses = [200, 201];

Hatchet.error = console.error;

// install RSVP error handler for uncaught(!) errors
RSVP.on('error', function (reason) {
    var resolverName = "";
    if (Hatchet.resolver.instance) {
        resolverName = Hatchet.resolver.instance.settings.name + " - ";
    }
    if (reason) {
        Hatchet.error(resolverName + 'Uncaught error:', reason);
    } else {
        Hatchet.error(resolverName + 'Uncaught error: error thrown from RSVP but it was empty');
    }
});

/**
 * Compares versions strings
 * (version1 < version2) == -1
 * (version1 = version2) == 0
 * (version1 > version2) == 1
 */
Hatchet.versionCompare = function (version1, version2) {
    var v1 = version1.split('.').map(function (item) {
        return parseInt(item);
    });
    var v2 = version2.split('.').map(function (item) {
        return parseInt(item);
    });
    var length = Math.max(v1.length, v2.length);
    var i = 0;

    for (; i < length; i++) {
        if (typeof v1[i] == "undefined" || v1[i] === null) {
            if (typeof v2[i] == "undefined" || v2[i] === null) {
                // v1 == v2
                return 0;
            } else if (v2[i] === 0) {
                continue;
            } else {
                // v1 < v2
                return -1;
            }
        } else if (typeof v2[i] == "undefined" || v2[i] === null) {
            if (v1[i] === 0) {
                continue;
            } else {
                // v1 > v2
                return 1;
            }
        } else if (v2[i] > v1[i]) {
            // v1 < v2
            return -1;
        } else if (v2[i] < v1[i]) {
            // v1 > v2
            return 1;
        }
    }
    // v1 == v2
    return 0;
};

/**
 * Check if this is at least specified hatchet-api-version.
 */
Hatchet.atLeastVersion = function (version) {
    return (Hatchet.versionCompare(Hatchet.apiVersion, version) >= 0);
};

Hatchet.resolver = {
    scriptPath: Hatchet.resolverData().scriptPath
};

Hatchet.timestamp = function () {
    return Math.round(new Date() / 1000);
};

Hatchet.htmlDecode = (function () {
    // this prevents any overhead from creating the object each time
    var element = document.createElement('textarea');

    function decodeHTMLEntities(str) {
        if (str && typeof str === 'string') {
            str = str.replace(/</g, "&lt;");
            str = str.replace(/>/g, "&gt;");
            element.innerHTML = str;
            str = element.textContent;
            element.textContent = '';
        }

        return str;
    }

    return decodeHTMLEntities;
})();

Hatchet.dumpResult = function (result) {
    var results = result.results;
    Hatchet.log("Dumping " + results.length + " results for query " + result.qid + "...");
    for (var i = 0; i < results.length; i++) {
        Hatchet.log(results[i].artist + " - " + results[i].track + " | " + results[i].url);
    }

    Hatchet.log("Done.");
};

// javascript part of Hatchet-Object API
Hatchet.extend = function (object, members) {
    var F = function () {};
    F.prototype = object;
    var newObject = new F();

    for (var key in members) {
        newObject[key] = members[key];
    }

    return newObject;
};

//Deprecated for 0.9 resolvers. Reporting resolver capabilities is no longer necessary.
var HatchetResolverCapability = {
    NullCapability: 0,
    Browsable:      1,
    PlaylistSync:   2,
    AccountFactory: 4,
    UrlLookup:      8
};

//Deprecated for 0.9 resolvers. Use Hatchet.UrlType instead.
var HatchetUrlType = {
    Any: 0,
    Playlist: 1,
    Track: 2,
    Album: 4,
    Artist: 8,
    Xspf: 16
};

//Deprecated for 0.9 resolvers. Use Hatchet.ConfigTestResultType instead.
var HatchetConfigTestResultType = {
    Other: 0,
    Success: 1,
    Logout: 2,
    CommunicationError: 3,
    InvalidCredentials: 4,
    InvalidAccount: 5,
    PlayingElsewhere: 6,
    AccountExpired: 7
};

/**
 * Resolver BaseObject, inherit it to implement your own resolver.
 */
var HatchetResolver = {
    init: function () {
    },
    scriptPath: function () {
        return Hatchet.resolverData().scriptPath;
    },
    getConfigUi: function () {
        return {};
    },
    getUserConfig: function () {
        return JSON.parse(window.localStorage[this.scriptPath()] || "{}");
    },
    saveUserConfig: function () {
        var configJson = JSON.stringify(Hatchet.resolverData().config);
        window.localStorage[this.scriptPath()] = configJson;
        this.newConfigSaved();
    },
    newConfigSaved: function () {
    },
    resolve: function (qid, artist, album, title) {
        return {
            qid: qid
        };
    },
    search: function (qid, searchString) {
        return this.resolve(qid, "", "", searchString);
    },
    artists: function (qid) {
        return {
            qid: qid
        };
    },
    albums: function (qid, artist) {
        return {
            qid: qid
        };
    },
    tracks: function (qid, artist, album) {
        return {
            qid: qid
        };
    },
    collection: function () {
        return {};
    },
    _adapter_testConfig: function (config) {
        return RSVP.Promise.resolve(this.testConfig(config)).then(function () {
            return {result: Hatchet.ConfigTestResultType.Success};
        });
    },
    testConfig: function () {
        this.configTest();
    },
    getStreamUrl: function (qid, url) {
        Hatchet.reportStreamUrl(qid, url);
    }
};

Hatchet.Resolver = {
    init: function () {
    },
    scriptPath: function () {
        return Hatchet.resolverData().scriptPath;
    },
    getConfigUi: function () {
        return {};
    },
    getUserConfig: function () {
        return JSON.parse(window.localStorage[this.scriptPath()] || "{}");
    },
    saveUserConfig: function () {
        window.localStorage[this.scriptPath()] = JSON.stringify(Hatchet.resolverData().config);
        this.newConfigSaved(Hatchet.resolverData().config);
    },
    newConfigSaved: function () {
    },
    testConfig: function () {
    },
    getStreamUrl: function (params) {
        return params;
    },
    getDownloadUrl: function (params) {
        return params;
    },
    resolve: function() {
    },
    _adapter_resolve: function (params) {
        return RSVP.Promise.resolve(this.resolve(params)).then(function (results) {
            if(Array.isArray(results)) {
                return {
                    'tracks': results
                };
            }

            return results;
        });
    },

    _adapter_search: function (params) {
        return RSVP.Promise.resolve(this.search(params)).then(function (results) {
            if(Array.isArray(results)) {
                return {
                    'tracks': results
                };
            }

            return results;
        });
    },

    _adapter_testConfig: function (config) {
        return RSVP.Promise.resolve(this.testConfig(config)).then(function (results) {
            results = results || Hatchet.ConfigTestResultType.Success;
            return results;
        }, function (error) {
            return error;
        });
    }
};

// help functions

Hatchet.valueForSubNode = function (node, tag) {
    if (node === undefined) {
        throw new Error("Hatchet.valueForSubnode: node is undefined!");
    }

    var element = node.getElementsByTagName(tag)[0];
    if (element === undefined) {
        return undefined;
    }

    return element.textContent;
};

/**
 * Internal counter used to identify retrievedMetadata call back from native
 * code.
 */
Hatchet.retrieveMetadataIdCounter = 0;
/**
 * Internal map used to map metadataIds to the respective JavaScript callbacks.
 */
Hatchet.retrieveMetadataCallbacks = {};

/**
 * Retrieve metadata for a media stream.
 *
 * @param url String The URL which should be scanned for metadata.
 * @param mimetype String The mimetype of the stream, e.g. application/ogg
 * @param sizehint Size in bytes if not supplied possibly the whole file needs
 *          to be downloaded
 * @param options Object Map to specify various parameters related to the media
 *          URL. This includes:
 *          * headers: Object of HTTP(S) headers that should be set on doing the
 *                     request.
 *          * method: String HTTP verb to be used (default: GET)
 *          * username: Username when using authentication
 *          * password: Password when using authentication
 * @param callback Function(Object,String) This function is called on completeion.
 *          If an error occured, error is set to the corresponding message else
 *          null.
 */
Hatchet.retrieveMetadata = function (url, mimetype, sizehint, options, callback) {
    var metadataId = Hatchet.retrieveMetadataIdCounter;
    Hatchet.retrieveMetadataIdCounter++;
    Hatchet.retrieveMetadataCallbacks[metadataId] = callback;
    Hatchet.nativeRetrieveMetadata(metadataId, url, mimetype, sizehint, options);
};

/**
 * Pass the natively retrieved metadata back to the JavaScript callback.
 *
 * Internal use only!
 */
Hatchet.retrievedMetadata = function (metadataId, metadata, error) {
    // Check that we have a matching callback stored.
    if (!Hatchet.retrieveMetadataCallbacks.hasOwnProperty(metadataId)) {
        return;
    }

    // Call the real callback
    if (Hatchet.retrieveMetadataCallbacks.hasOwnProperty(metadataId)) {
        Hatchet.retrieveMetadataCallbacks[metadataId](metadata, error);
    }

    // Callback are only used once.
    delete Hatchet.retrieveMetadataCallbacks[metadataId];
};

/**
 * This method is externalized from Hatchet.asyncRequest, so that other clients
 * (like hatchet-android) can inject their own logic that determines whether or not to do a request
 * natively.
 *
 * @returns boolean indicating whether or not to do a request with the given parameters natively
 */
var shouldDoNativeRequest = function (options) {
    var extraHeaders = options.headers;
    return (extraHeaders && (extraHeaders.hasOwnProperty("Referer")
        || extraHeaders.hasOwnProperty("referer")
        || extraHeaders.hasOwnProperty("User-Agent")));
};

/**
 * Possible options:
 *  - url: The URL to call
 *  - method: The HTTP request method (default: GET)
 *  - username: The username for HTTP Basic Auth
 *  - password: The password for HTTP Basic Auth
 *  - errorHandler: callback called if the request was not completed
 *  - data: body data included in POST requests
 *  - needCookieHeader: boolean indicating whether or not the request needs to be able to get the
 *                      "Set-Cookie" response header
 *  - headers: headers set on the request
 */
var doRequest = function(options) {
    if (shouldDoNativeRequest(options)) {
        return Hatchet.NativeScriptJobManager.invoke('httpRequest', options).then(function(xhr) {
            xhr.responseHeaders = xhr.responseHeaders || {};
            xhr.getAllResponseHeaders = function() {
                return this.responseHeaders;
            };
            xhr.getResponseHeader = function (header) {
                for(key in xhr.responseHeaders) {
                    if(key.toLowerCase() === header.toLowerCase()) {
                        return xhr.responseHeaders[key];
                    }
                }
                return null;
            };

            return xhr;
        });
    } else {
        return new RSVP.Promise(function(resolve, reject) {
            var xmlHttpRequest = new XMLHttpRequest();
            xmlHttpRequest.open(options.method, options.url, true, options.username, options.password);
            if (options.headers) {
                for (var headerName in options.headers) {
                    xmlHttpRequest.setRequestHeader(headerName, options.headers[headerName]);
                }
            }
            xmlHttpRequest.onreadystatechange = function () {
                if (xmlHttpRequest.readyState == 4
                    && httpSuccessStatuses.indexOf(xmlHttpRequest.status) != -1) {
                    resolve(xmlHttpRequest);
                } else if (xmlHttpRequest.readyState === 4) {
                    Hatchet.log("Failed to do " + options.method + " request: to: " + options.url);
                    Hatchet.log("Status Code was: " + xmlHttpRequest.status);
                    reject(xmlHttpRequest);
                }
            };
            xmlHttpRequest.send(options.data || null);
        });
    }
};

Hatchet.ajax = function (url, settings) {
    if (typeof url === "object") {
        settings = url;
    } else {
        settings = settings || {};
        settings.url = url;
    }

    settings.type = settings.type || settings.method || 'get';
    settings.method = settings.type;
    settings.dataFormat = settings.dataFormat || 'form';

    if (settings.data) {
        var formEncode = function (obj) {
            var str = [];
            for (var p in obj) {
                if (obj[p] !== undefined) {
                    if (Array.isArray(obj[p])) {
                        for (var i = 0; i < obj[p].length; i++) {
                            str.push(encodeURIComponent(p) + "=" + encodeURIComponent(obj[p][i]));
                        }
                    } else {
                        str.push(encodeURIComponent(p) + "=" + encodeURIComponent(obj[p]));
                    }
                }
            }

            str.sort();

            return str.join("&");
        };
        if (typeof settings.data === 'object') {
            if (settings.dataFormat == 'form') {
                settings.data = formEncode(settings.data);
                settings.contentType = settings.contentType || 'application/x-www-form-urlencoded';
            } else if (settings.dataFormat == 'json') {
                settings.data = JSON.stringify(settings.data);
                settings.contentType = settings.contentType || 'application/json';
            } else {
                throw new Error("Hatchet.ajax: unknown dataFormat requested: "
                    + settings.dataFormat);
            }
        } else {
            throw new Error("Hatchet.ajax: data should be either object or string");
        }

        if (settings.type.toLowerCase() === 'get') {
            settings.url += '?' + settings.data;
            delete settings.data;
        } else {
            settings.headers = settings.headers || {};
            if (!settings.headers.hasOwnProperty('Content-Type')) {
                settings.headers['Content-Type'] = settings.contentType;
            }
        }
    }

    return doRequest(settings).then(function (xhr) {
            if (settings.rawResponse) {
                return xhr;
            }
            var responseText = xhr.responseText;
            var contentType;
            if (settings.dataType === 'json') {
                contentType = 'application/json';
            } else if (settings.dataType === 'xml') {
                contentType = 'text/xml';
            } else if (typeof xhr.getResponseHeader !== 'undefined') {
                contentType = xhr.getResponseHeader('Content-Type');
            } else if (xhr.hasOwnProperty('contentType')) {
                contentType = xhr['contentType'];
            } else {
                contentType = 'text/html';
            }

            if (~contentType.indexOf('application/json')) {
                return JSON.parse(responseText);
            }

            if (~contentType.indexOf('text/xml')) {
                var domParser = new DOMParser();
                return domParser.parseFromString(responseText, "text/xml");
            }

            return xhr.responseText;
        });
};

Hatchet.post = function (url, settings) {
    if (typeof url === "object") {
        settings = url;
    } else {
        settings = settings || {};
        settings.url = url;
    }

    settings.method = 'POST';

    return Hatchet.ajax(settings);
};

Hatchet.get = function (url, settings) {
    return Hatchet.ajax(url, settings);
};

Hatchet.assert = function (assertion, message) {
    Hatchet.nativeAssert(assertion, message);
};

Hatchet.sha256 = Hatchet.sha256 || function (message) {
        return CryptoJS.SHA256(message).toString(CryptoJS.enc.Hex);
    };
Hatchet.md5 = Hatchet.md5 || function (message) {
        return CryptoJS.MD5(message).toString(CryptoJS.enc.Hex);
    };
// Return a HMAC (md5) signature of the input text with the desired key
Hatchet.hmac = function (key, message) {
    return CryptoJS.HmacMD5(message, key).toString(CryptoJS.enc.Hex);
};

// Extracted from https://github.com/andrewrk/diacritics version 1.2.0
// Thanks to Andrew Kelley for this MIT-licensed diacritic removal code
// Initialisation / precomputation
(function() {
    var replacementList = [
        {base: ' ', chars: "\u00A0"},
        {base: '0', chars: "\u07C0"},
        {base: 'A', chars: "\u24B6\uFF21\u00C0\u00C1\u00C2\u1EA6\u1EA4\u1EAA\u1EA8\u00C3\u0100\u0102\u1EB0\u1EAE\u1EB4\u1EB2\u0226\u01E0\u00C4\u01DE\u1EA2\u00C5\u01FA\u01CD\u0200\u0202\u1EA0\u1EAC\u1EB6\u1E00\u0104\u023A\u2C6F"},
        {base: 'AA', chars: "\uA732"},
        {base: 'AE', chars: "\u00C6\u01FC\u01E2"},
        {base: 'AO', chars: "\uA734"},
        {base: 'AU', chars: "\uA736"},
        {base: 'AV', chars: "\uA738\uA73A"},
        {base: 'AY', chars: "\uA73C"},
        {base: 'B', chars: "\u24B7\uFF22\u1E02\u1E04\u1E06\u0243\u0181"},
        {base: 'C', chars: "\uFF43\u24b8\uff23\uA73E\u1E08"},
        {base: 'D', chars: "\u24B9\uFF24\u1E0A\u010E\u1E0C\u1E10\u1E12\u1E0E\u0110\u018A\u0189\u1D05\uA779"},
        {base: 'Dh', chars: "\u00D0"},
        {base: 'DZ', chars: "\u01F1\u01C4"},
        {base: 'Dz', chars: "\u01F2\u01C5"},
        {base: 'E', chars: "\u025B\u24BA\uFF25\u00C8\u00C9\u00CA\u1EC0\u1EBE\u1EC4\u1EC2\u1EBC\u0112\u1E14\u1E16\u0114\u0116\u00CB\u1EBA\u011A\u0204\u0206\u1EB8\u1EC6\u0228\u1E1C\u0118\u1E18\u1E1A\u0190\u018E\u1D07"},
        {base: 'F', chars: "\uA77C\u24BB\uFF26\u1E1E\u0191\uA77B"},
        {base: 'G', chars: "\u24BC\uFF27\u01F4\u011C\u1E20\u011E\u0120\u01E6\u0122\u01E4\u0193\uA7A0\uA77D\uA77E\u0262"},
        {base: 'H', chars: "\u24BD\uFF28\u0124\u1E22\u1E26\u021E\u1E24\u1E28\u1E2A\u0126\u2C67\u2C75\uA78D"},
        {base: 'I', chars: "\u24BE\uFF29\xCC\xCD\xCE\u0128\u012A\u012C\u0130\xCF\u1E2E\u1EC8\u01CF\u0208\u020A\u1ECA\u012E\u1E2C\u0197"},
        {base: 'J', chars: "\u24BF\uFF2A\u0134\u0248\u0237"},
        {base: 'K', chars: "\u24C0\uFF2B\u1E30\u01E8\u1E32\u0136\u1E34\u0198\u2C69\uA740\uA742\uA744\uA7A2"},
        {base: 'L', chars: "\u24C1\uFF2C\u013F\u0139\u013D\u1E36\u1E38\u013B\u1E3C\u1E3A\u0141\u023D\u2C62\u2C60\uA748\uA746\uA780"},
        {base: 'LJ', chars: "\u01C7"},
        {base: 'Lj', chars: "\u01C8"},
        {base: 'M', chars: "\u24C2\uFF2D\u1E3E\u1E40\u1E42\u2C6E\u019C\u03FB"},
        {base: 'N', chars: "\uA7A4\u0220\u24C3\uFF2E\u01F8\u0143\xD1\u1E44\u0147\u1E46\u0145\u1E4A\u1E48\u019D\uA790\u1D0E"},
        {base: 'NJ', chars: "\u01CA"},
        {base: 'Nj', chars: "\u01CB"},
        {base: 'O', chars: "\u24C4\uFF2F\xD2\xD3\xD4\u1ED2\u1ED0\u1ED6\u1ED4\xD5\u1E4C\u022C\u1E4E\u014C\u1E50\u1E52\u014E\u022E\u0230\xD6\u022A\u1ECE\u0150\u01D1\u020C\u020E\u01A0\u1EDC\u1EDA\u1EE0\u1EDE\u1EE2\u1ECC\u1ED8\u01EA\u01EC\xD8\u01FE\u0186\u019F\uA74A\uA74C"},
        {base: 'OE', chars: "\u0152"},
        {base: 'OI', chars: "\u01A2"},
        {base: 'OO', chars: "\uA74E"},
        {base: 'OU', chars: "\u0222"},
        {base: 'P', chars: "\u24C5\uFF30\u1E54\u1E56\u01A4\u2C63\uA750\uA752\uA754"},
        {base: 'Q', chars: "\u24C6\uFF31\uA756\uA758\u024A"},
        {base: 'R', chars: "\u24C7\uFF32\u0154\u1E58\u0158\u0210\u0212\u1E5A\u1E5C\u0156\u1E5E\u024C\u2C64\uA75A\uA7A6\uA782"},
        {base: 'S', chars: "\u24C8\uFF33\u1E9E\u015A\u1E64\u015C\u1E60\u0160\u1E66\u1E62\u1E68\u0218\u015E\u2C7E\uA7A8\uA784"},
        {base: 'T', chars: "\u24C9\uFF34\u1E6A\u0164\u1E6C\u021A\u0162\u1E70\u1E6E\u0166\u01AC\u01AE\u023E\uA786"},
        {base: 'Th', chars: "\u00DE"},
        {base: 'TZ', chars: "\uA728"},
        {base: 'U', chars: "\u24CA\uFF35\xD9\xDA\xDB\u0168\u1E78\u016A\u1E7A\u016C\xDC\u01DB\u01D7\u01D5\u01D9\u1EE6\u016E\u0170\u01D3\u0214\u0216\u01AF\u1EEA\u1EE8\u1EEE\u1EEC\u1EF0\u1EE4\u1E72\u0172\u1E76\u1E74\u0244"},
        {base: 'V', chars: "\u24CB\uFF36\u1E7C\u1E7E\u01B2\uA75E\u0245"},
        {base: 'VY', chars: "\uA760"},
        {base: 'W', chars: "\u24CC\uFF37\u1E80\u1E82\u0174\u1E86\u1E84\u1E88\u2C72"},
        {base: 'X', chars: "\u24CD\uFF38\u1E8A\u1E8C"},
        {base: 'Y', chars: "\u24CE\uFF39\u1EF2\xDD\u0176\u1EF8\u0232\u1E8E\u0178\u1EF6\u1EF4\u01B3\u024E\u1EFE"},
        {base: 'Z', chars: "\u24CF\uFF3A\u0179\u1E90\u017B\u017D\u1E92\u1E94\u01B5\u0224\u2C7F\u2C6B\uA762"},
        {base: 'a', chars: "\u24D0\uFF41\u1E9A\u00E0\u00E1\u00E2\u1EA7\u1EA5\u1EAB\u1EA9\u00E3\u0101\u0103\u1EB1\u1EAF\u1EB5\u1EB3\u0227\u01E1\u00E4\u01DF\u1EA3\u00E5\u01FB\u01CE\u0201\u0203\u1EA1\u1EAD\u1EB7\u1E01\u0105\u2C65\u0250\u0251"},
        {base: 'aa', chars: "\uA733"},
        {base: 'ae', chars: "\u00E6\u01FD\u01E3"},
        {base: 'ao', chars: "\uA735"},
        {base: 'au', chars: "\uA737"},
        {base: 'av', chars: "\uA739\uA73B"},
        {base: 'ay', chars: "\uA73D"},
        {base: 'b', chars: "\u24D1\uFF42\u1E03\u1E05\u1E07\u0180\u0183\u0253\u0182"},
        {base: 'c', chars: "\u24D2\u0107\u0109\u010B\u010D\u00E7\u1E09\u0188\u023C\uA73F\u2184\u0043\u0106\u0108\u010A\u010C\u00C7\u0187\u023B"},
        {base: 'd', chars: "\u24D3\uFF44\u1E0B\u010F\u1E0D\u1E11\u1E13\u1E0F\u0111\u018C\u0256\u0257\u018B\u13E7\u0501\uA7AA"},
        {base: 'dh', chars: "\u00F0"},
        {base: 'dz', chars: "\u01F3\u01C6"},
        {base: 'e', chars: "\u24D4\uFF45\u00E8\u00E9\u00EA\u1EC1\u1EBF\u1EC5\u1EC3\u1EBD\u0113\u1E15\u1E17\u0115\u0117\u00EB\u1EBB\u011B\u0205\u0207\u1EB9\u1EC7\u0229\u1E1D\u0119\u1E19\u1E1B\u0247\u01DD"},
        {base: 'f', chars: "\u24D5\uFF46\u1E1F\u0192"},
        {base: 'ff', chars: "\uFB00"},
        {base: 'fi', chars: "\uFB01"},
        {base: 'fl', chars: "\uFB02"},
        {base: 'ffi', chars: "\uFB03"},
        {base: 'ffl', chars: "\uFB04"},
        {base: 'g', chars: "\u24D6\uFF47\u01F5\u011D\u1E21\u011F\u0121\u01E7\u0123\u01E5\u0260\uA7A1\uA77F\u1D79"},
        {base: 'h', chars: "\u24D7\uFF48\u0125\u1E23\u1E27\u021F\u1E25\u1E29\u1E2B\u1E96\u0127\u2C68\u2C76\u0265"},
        {base: 'hv', chars: "\u0195"},
        {base: 'i', chars: "\u24D8\uFF49\xEC\xED\xEE\u0129\u012B\u012D\xEF\u1E2F\u1EC9\u01D0\u0209\u020B\u1ECB\u012F\u1E2D\u0268\u0131"},
        {base: 'j', chars: "\u24D9\uFF4A\u0135\u01F0\u0249"},
        {base: 'k', chars: "\u24DA\uFF4B\u1E31\u01E9\u1E33\u0137\u1E35\u0199\u2C6A\uA741\uA743\uA745\uA7A3"},
        {base: 'l', chars: "\u24DB\uFF4C\u0140\u013A\u013E\u1E37\u1E39\u013C\u1E3D\u1E3B\u017F\u0142\u019A\u026B\u2C61\uA749\uA781\uA747\u026D"},
        {base: 'lj', chars: "\u01C9"},
        {base: 'm', chars: "\u24DC\uFF4D\u1E3F\u1E41\u1E43\u0271\u026F"},
        {base: 'n', chars: "\u24DD\uFF4E\u01F9\u0144\xF1\u1E45\u0148\u1E47\u0146\u1E4B\u1E49\u019E\u0272\u0149\uA791\uA7A5\u043B\u0509"},
        {base: 'nj', chars: "\u01CC"},
        {base: 'o', chars: "\u24DE\uFF4F\xF2\xF3\xF4\u1ED3\u1ED1\u1ED7\u1ED5\xF5\u1E4D\u022D\u1E4F\u014D\u1E51\u1E53\u014F\u022F\u0231\xF6\u022B\u1ECF\u0151\u01D2\u020D\u020F\u01A1\u1EDD\u1EDB\u1EE1\u1EDF\u1EE3\u1ECD\u1ED9\u01EB\u01ED\xF8\u01FF\uA74B\uA74D\u0275\u0254\u1D11"},
        {base: 'oe', chars: "\u0153"},
        {base: 'oi', chars: "\u01A3"},
        {base: 'oo', chars: "\uA74F"},
        {base: 'ou', chars: "\u0223"},
        {base: 'p', chars: "\u24DF\uFF50\u1E55\u1E57\u01A5\u1D7D\uA751\uA753\uA755\u03C1"},
        {base: 'q', chars: "\u24E0\uFF51\u024B\uA757\uA759"},
        {base: 'r', chars: "\u24E1\uFF52\u0155\u1E59\u0159\u0211\u0213\u1E5B\u1E5D\u0157\u1E5F\u024D\u027D\uA75B\uA7A7\uA783"},
        {base: 's', chars: "\u24E2\uFF53\u015B\u1E65\u015D\u1E61\u0161\u1E67\u1E63\u1E69\u0219\u015F\u023F\uA7A9\uA785\u1E9B\u0282"},
        {base: 'ss', chars: "\xDF"},
        {base: 't', chars: "\u24E3\uFF54\u1E6B\u1E97\u0165\u1E6D\u021B\u0163\u1E71\u1E6F\u0167\u01AD\u0288\u2C66\uA787"},
        {base: 'th', chars: "\u00FE"},
        {base: 'tz', chars: "\uA729"},
        {base: 'u', chars: "\u24E4\uFF55\xF9\xFA\xFB\u0169\u1E79\u016B\u1E7B\u016D\xFC\u01DC\u01D8\u01D6\u01DA\u1EE7\u016F\u0171\u01D4\u0215\u0217\u01B0\u1EEB\u1EE9\u1EEF\u1EED\u1EF1\u1EE5\u1E73\u0173\u1E77\u1E75\u0289"},
        {base: 'v', chars: "\u24E5\uFF56\u1E7D\u1E7F\u028B\uA75F\u028C"},
        {base: 'vy', chars: "\uA761"},
        {base: 'w', chars: "\u24E6\uFF57\u1E81\u1E83\u0175\u1E87\u1E85\u1E98\u1E89\u2C73"},
        {base: 'x', chars: "\u24E7\uFF58\u1E8B\u1E8D"},
        {base: 'y', chars: "\u24E8\uFF59\u1EF3\xFD\u0177\u1EF9\u0233\u1E8F\xFF\u1EF7\u1E99\u1EF5\u01B4\u024F\u1EFF"},
        {base: 'z', chars: "\u24E9\uFF5A\u017A\u1E91\u017C\u017E\u1E93\u1E95\u01B6\u0225\u0240\u2C6C\uA763"}
    ];

    Hatchet.diacriticsMap = {};
    var i, j, chars;
    for (i = 0; i < replacementList.length; i += 1) {
        chars = replacementList[i].chars;
        for (j = 0; j < chars.length; j += 1) {
            Hatchet.diacriticsMap[chars[j]] = replacementList[i].base;
        }
    }
})();

Hatchet.removeDiacritics = function (str) {
    return str.replace(/[^\u0000-\u007E]/g, function (c) {
        return Hatchet.diacriticsMap[c] || c;
    });
};

Hatchet.localStorage = Hatchet.localStorage || {
        setItem: function (key, value) {
            window.localStorage[key] = value;
        },
        getItem: function (key) {
            return window.localStorage[key];
        },
        removeItem: function (key) {
            delete window.localStorage[key];
        }
    };

// some aliases
Hatchet.setTimeout = Hatchet.setTimeout || window.setTimeout;
Hatchet.setInterval = Hatchet.setInterval || window.setInterval;
Hatchet.base64Decode = function (a) {
    return window.atob(a);
};
Hatchet.base64Encode = function (b) {
    return window.btoa(b);
};

Hatchet.PluginManager = {
    wrapperPrefix: '_adapter_',
    objects: {},
    objectCounter: 0,
    identifyObject: function (object) {
        if (!object.hasOwnProperty('id')) {
            object.id = this.objectCounter++;
        }

        return object.id;
    },
    registerPlugin: function (type, object) {
        this.objects[this.identifyObject(object)] = object;
        Hatchet.log("registerPlugin: " + type + " id: " + object.id);
        Hatchet.registerScriptPlugin(type, object.id);
    },

    unregisterPlugin: function (type, object) {
        this.objects[this.identifyObject(object)] = object;

        Hatchet.log("unregisterPlugin: " + type + " id: " + object.id);
        Hatchet.unregisterScriptPlugin(type, object.id);
    },

    resolve: [],
    invokeSync: function (requestId, objectId, methodName, params) {
        if (this.objects[objectId][this.wrapperPrefix + methodName]) {
            methodName = this.wrapperPrefix + methodName;
        }

        if (!this.objects[objectId]) {
            Hatchet.log("Object not found! objectId: " + objectId + " methodName: " + methodName);
        } else {
            if (!this.objects[objectId][methodName]) {
                Hatchet.log("Function not found: " + methodName);
            }
        }

        if (typeof this.objects[objectId][methodName] !== 'function' && this.objects[objectId][methodName]) {
            return this.objects[objectId][methodName];
        } else if (typeof this.objects[objectId][methodName] !== 'function') {
            throw new Error('\'' + methodName + '\' on ScriptObject ' + objectId + ' is not a function', typeof this.objects[objectId][methodName]);
        }

        return this.objects[objectId][methodName](params);
    },

    invoke: function (requestId, objectId, methodName, params) {
        RSVP.Promise.resolve(this.invokeSync(requestId, objectId, methodName, params))
            .then(function (result) {
                var params = {
                    requestId: requestId,
                    data: result
                };
                Hatchet.reportScriptJobResults(encodeParamsToNativeFunctions(params));
            }, function (error) {
                var params = {
                    requestId: requestId,
                    error: error
                };
                Hatchet.reportScriptJobResults(encodeParamsToNativeFunctions(params));
            });
    }
};

var encodeParamsToNativeFunctions = function(param) {
  return param;
};

Hatchet.NativeScriptJobManager = {
    idCounter: 0,
    deferreds: {},
    invoke: function (methodName, params) {
        params = params || {};

        var requestId = this.idCounter++;
        var deferred = RSVP.defer();
        this.deferreds[requestId] = deferred;
        Hatchet.invokeNativeScriptJob(requestId, methodName, encodeParamsToNativeFunctions(params));
        return deferred.promise;
    },
    reportNativeScriptJobResult: function(requestId, result) {
        var deferred = this.deferreds[requestId];
        if (!deferred) {
            Hatchet.log("Deferred object with the given requestId is not present!");
        }
        deferred.resolve(result);
        delete this.deferreds[requestId];
    },
    reportNativeScriptJobError: function(requestId, error) {
        var deferred = this.deferreds[requestId];
        if (!deferred) {
            console.log("Deferred object with the given requestId is not present!");
        }
        deferred.reject(error);
        delete this.deferreds[requestId];
    }
};

Hatchet.UrlType = {
    Any: 0,
    Playlist: 1,
    Track: 2,
    Album: 3,
    Artist: 4,
    XspfPlaylist: 5
};

Hatchet.ConfigTestResultType = {
    Other: 0,
    Success: 1,
    Logout: 2,
    CommunicationError: 3,
    InvalidCredentials: 4,
    InvalidAccount: 5,
    PlayingElsewhere: 6,
    AccountExpired: 7
};

Hatchet.Country = {
    AnyCountry: 0,
    Afghanistan: 1,
    Albania: 2,
    Algeria: 3,
    AmericanSamoa: 4,
    Andorra: 5,
    Angola: 6,
    Anguilla: 7,
    Antarctica: 8,
    AntiguaAndBarbuda: 9,
    Argentina: 10,
    Armenia: 11,
    Aruba: 12,
    Australia: 13,
    Austria: 14,
    Azerbaijan: 15,
    Bahamas: 16,
    Bahrain: 17,
    Bangladesh: 18,
    Barbados: 19,
    Belarus: 20,
    Belgium: 21,
    Belize: 22,
    Benin: 23,
    Bermuda: 24,
    Bhutan: 25,
    Bolivia: 26,
    BosniaAndHerzegowina: 27,
    Botswana: 28,
    BouvetIsland: 29,
    Brazil: 30,
    BritishIndianOceanTerritory: 31,
    BruneiDarussalam: 32,
    Bulgaria: 33,
    BurkinaFaso: 34,
    Burundi: 35,
    Cambodia: 36,
    Cameroon: 37,
    Canada: 38,
    CapeVerde: 39,
    CaymanIslands: 40,
    CentralAfricanRepublic: 41,
    Chad: 42,
    Chile: 43,
    China: 44,
    ChristmasIsland: 45,
    CocosIslands: 46,
    Colombia: 47,
    Comoros: 48,
    DemocraticRepublicOfCongo: 49,
    PeoplesRepublicOfCongo: 50,
    CookIslands: 51,
    CostaRica: 52,
    IvoryCoast: 53,
    Croatia: 54,
    Cuba: 55,
    Cyprus: 56,
    CzechRepublic: 57,
    Denmark: 58,
    Djibouti: 59,
    Dominica: 60,
    DominicanRepublic: 61,
    EastTimor: 62,
    Ecuador: 63,
    Egypt: 64,
    ElSalvador: 65,
    EquatorialGuinea: 66,
    Eritrea: 67,
    Estonia: 68,
    Ethiopia: 69,
    FalklandIslands: 70,
    FaroeIslands: 71,
    FijiCountry: 72,
    Finland: 73,
    France: 74,
    MetropolitanFrance: 75,
    FrenchGuiana: 76,
    FrenchPolynesia: 77,
    FrenchSouthernTerritories: 78,
    Gabon: 79,
    Gambia: 80,
    Georgia: 81,
    Germany: 82,
    Ghana: 83,
    Gibraltar: 84,
    Greece: 85,
    Greenland: 86,
    Grenada: 87,
    Guadeloupe: 88,
    Guam: 89,
    Guatemala: 90,
    Guinea: 91,
    GuineaBissau: 92,
    Guyana: 93,
    Haiti: 94,
    HeardAndMcDonaldIslands: 95,
    Honduras: 96,
    HongKong: 97,
    Hungary: 98,
    Iceland: 99,
    India: 100,
    Indonesia: 101,
    Iran: 102,
    Iraq: 103,
    Ireland: 104,
    Israel: 105,
    Italy: 106,
    Jamaica: 107,
    Japan: 108,
    Jordan: 109,
    Kazakhstan: 110,
    Kenya: 111,
    Kiribati: 112,
    DemocraticRepublicOfKorea: 113,
    RepublicOfKorea: 114,
    Kuwait: 115,
    Kyrgyzstan: 116,
    Lao: 117,
    Latvia: 118,
    Lebanon: 119,
    Lesotho: 120,
    Liberia: 121,
    LibyanArabJamahiriya: 122,
    Liechtenstein: 123,
    Lithuania: 124,
    Luxembourg: 125,
    Macau: 126,
    Macedonia: 127,
    Madagascar: 128,
    Malawi: 129,
    Malaysia: 130,
    Maldives: 131,
    Mali: 132,
    Malta: 133,
    MarshallIslands: 134,
    Martinique: 135,
    Mauritania: 136,
    Mauritius: 137,
    Mayotte: 138,
    Mexico: 139,
    Micronesia: 140,
    Moldova: 141,
    Monaco: 142,
    Mongolia: 143,
    Montserrat: 144,
    Morocco: 145,
    Mozambique: 146,
    Myanmar: 147,
    Namibia: 148,
    NauruCountry: 149,
    Nepal: 150,
    Netherlands: 151,
    NetherlandsAntilles: 152,
    NewCaledonia: 153,
    NewZealand: 154,
    Nicaragua: 155,
    Niger: 156,
    Nigeria: 157,
    Niue: 158,
    NorfolkIsland: 159,
    NorthernMarianaIslands: 160,
    Norway: 161,
    Oman: 162,
    Pakistan: 163,
    Palau: 164,
    PalestinianTerritory: 165,
    Panama: 166,
    PapuaNewGuinea: 167,
    Paraguay: 168,
    Peru: 169,
    Philippines: 170,
    Pitcairn: 171,
    Poland: 172,
    Portugal: 173,
    PuertoRico: 174,
    Qatar: 175,
    Reunion: 176,
    Romania: 177,
    RussianFederation: 178,
    Rwanda: 179,
    SaintKittsAndNevis: 180,
    StLucia: 181,
    StVincentAndTheGrenadines: 182,
    Samoa: 183,
    SanMarino: 184,
    SaoTomeAndPrincipe: 185,
    SaudiArabia: 186,
    Senegal: 187,
    SerbiaAndMontenegro: 241,
    Seychelles: 188,
    SierraLeone: 189,
    Singapore: 190,
    Slovakia: 191,
    Slovenia: 192,
    SolomonIslands: 193,
    Somalia: 194,
    SouthAfrica: 195,
    SouthGeorgiaAndTheSouthSandwichIslands: 196,
    Spain: 197,
    SriLanka: 198,
    StHelena: 199,
    StPierreAndMiquelon: 200,
    Sudan: 201,
    Suriname: 202,
    SvalbardAndJanMayenIslands: 203,
    Swaziland: 204,
    Sweden: 205,
    Switzerland: 206,
    SyrianArabRepublic: 207,
    Taiwan: 208,
    Tajikistan: 209,
    Tanzania: 210,
    Thailand: 211,
    Togo: 212,
    Tokelau: 213,
    TongaCountry: 214,
    TrinidadAndTobago: 215,
    Tunisia: 216,
    Turkey: 217,
    Turkmenistan: 218,
    TurksAndCaicosIslands: 219,
    Tuvalu: 220,
    Uganda: 221,
    Ukraine: 222,
    UnitedArabEmirates: 223,
    UnitedKingdom: 224,
    UnitedStates: 225,
    UnitedStatesMinorOutlyingIslands: 226,
    Uruguay: 227,
    Uzbekistan: 228,
    Vanuatu: 229,
    VaticanCityState: 230,
    Venezuela: 231,
    VietNam: 232,
    BritishVirginIslands: 233,
    USVirginIslands: 234,
    WallisAndFutunaIslands: 235,
    WesternSahara: 236,
    Yemen: 237,
    Yugoslavia: 238,
    Zambia: 239,
    Zimbabwe: 240,
    Montenegro: 242,
    Serbia: 243,
    SaintBarthelemy: 244,
    SaintMartin: 245,
    LatinAmericaAndTheCaribbean: 246
};

Hatchet.Collection = {
    BrowseCapability: {
        Artists: 1,
        Albums: 2,
        Tracks: 4
    },

    cachedDbs: {},

    Transaction: function (collection, id) {

        this.ensureDb = function () {
            return new RSVP.Promise(function (resolve, reject) {
                if (!collection.cachedDbs.hasOwnProperty(id)) {
                    Hatchet.log("Opening database");
                    var estimatedSize = 5 * 1024 * 1024; // 5MB
                    collection.cachedDbs[id] =
                        openDatabase(id + "_collection", "", "Collection", estimatedSize);

                    collection.cachedDbs[id].transaction(function (tx) {
                        Hatchet.log("Creating initial db tables");
                        tx.executeSql("CREATE TABLE IF NOT EXISTS artists(" +
                            "_id INTEGER PRIMARY KEY AUTOINCREMENT," +
                            "artist TEXT ," +
                            "artistDisambiguation TEXT," +
                            "UNIQUE (artist, artistDisambiguation) ON CONFLICT IGNORE)", []);
                        tx.executeSql("CREATE TABLE IF NOT EXISTS albumArtists(" +
                            "_id INTEGER PRIMARY KEY AUTOINCREMENT," +
                            "albumArtist TEXT ," +
                            "albumArtistDisambiguation TEXT," +
                            "UNIQUE (albumArtist, albumArtistDisambiguation) ON CONFLICT IGNORE)",
                            []);
                        tx.executeSql("CREATE TABLE IF NOT EXISTS albums(" +
                            "_id INTEGER PRIMARY KEY AUTOINCREMENT," +
                            "album TEXT," +
                            "albumArtistId INTEGER," +
                            "UNIQUE (album, albumArtistId) ON CONFLICT IGNORE," +
                            "FOREIGN KEY(albumArtistId) REFERENCES albumArtists(_id))", []);
                        tx.executeSql("CREATE TABLE IF NOT EXISTS artistAlbums(" +
                            "_id INTEGER PRIMARY KEY AUTOINCREMENT," +
                            "albumId INTEGER," +
                            "artistId INTEGER," +
                            "UNIQUE (albumId, artistId) ON CONFLICT IGNORE," +
                            "FOREIGN KEY(albumId) REFERENCES albums(_id)," +
                            "FOREIGN KEY(artistId) REFERENCES artists(_id))", []);
                        tx.executeSql("CREATE TABLE IF NOT EXISTS tracks(" +
                            "_id INTEGER PRIMARY KEY AUTOINCREMENT," +
                            "track TEXT," +
                            "artistId INTEGER," +
                            "albumId INTEGER," +
                            "url TEXT," +
                            "duration INTEGER," +
                            "albumPos INTEGER," +
                            "linkUrl TEXT," +
                            'releaseyear INTEGER,' +
                            'bitrate INTEGER,' +
                            "UNIQUE (track, artistId, albumId) ON CONFLICT IGNORE," +
                            "FOREIGN KEY(artistId) REFERENCES artists(_id)," +
                            "FOREIGN KEY(albumId) REFERENCES albums(_id))", []);
                    });
                }
                resolve(collection.cachedDbs[id]);
            });
        };

        this.beginTransaction = function () {
            var that = this;
            return this.ensureDb().then(function (db) {
                return new RSVP.Promise(function (resolve, reject) {
                    that.db = db;
                    that.statements = [];
                    resolve();
                })
            });
        };

        this.execDeferredStatements = function (resolve, reject) {
            var that = this;
            that.stmtsToResolve = that.statements.length;
            that.results = that.statements.slice();
            Hatchet.log('Executing ' + that.stmtsToResolve
                + ' deferred SQL statements in transaction');
            return new RSVP.Promise(function (resolve, reject) {
                if (that.statements.length == 0) {
                    resolve([]);
                } else {
                    that.db.transaction(function (tx) {
                        for (var i = 0; i < that.statements.length; ++i) {
                            var stmt = that.statements[i];
                            tx.executeSql(stmt.statement, stmt.args,
                                (function () {
                                    //A function returning a function to
                                    //capture value of i
                                    var originalI = i;
                                    return function (tx, results) {
                                        if (typeof that.statements[originalI].map !== 'undefined') {
                                            var map = that.statements[originalI].map;
                                            that.results[originalI] = [];
                                            for (var ii = 0; ii < results.rows.length; ii++) {
                                                that.results[originalI].push(map(
                                                    results.rows.item(ii)
                                                ));
                                            }
                                        }
                                        else {
                                            that.results[originalI] = results;
                                        }
                                        that.stmtsToResolve--;
                                        if (that.stmtsToResolve == 0) {
                                            that.statements = [];
                                            resolve(that.results);
                                        }
                                    };
                                })(), function (tx, error) {
                                    Hatchet.log("Error in tx.executeSql: " + error.code + " - "
                                        + error.message);
                                    that.statements = [];
                                    reject(error);
                                }
                            );
                        }
                    });
                }
            });
        };

        this.sql = function (sqlStatement, sqlArgs, mapFunction) {
            this.statements.push({statement: sqlStatement, args: sqlArgs, map: mapFunction});
        };

        this.sqlSelect = function (table, mapResults, fields, where, join) {
            var whereKeys = [];
            var whereValues = [];
            for (var whereKey in where) {
                if (where.hasOwnProperty(whereKey)) {
                    whereKeys.push(table + "." + whereKey + " = ?");
                    whereValues.push(where[whereKey]);
                }
            }
            var whereString = whereKeys.length > 0 ? " WHERE " + whereKeys.join(" AND ") : "";

            var joinString = "";
            for (var i = 0; join && i < join.length; i++) {
                var joinConditions = [];
                for (var joinKey in join[i].conditions) {
                    if (join[i].conditions.hasOwnProperty(joinKey)) {
                        joinConditions.push(table + "." + joinKey + " = " + join[i].table + "."
                            + join[i].conditions[joinKey]);
                    }
                }
                joinString += " INNER JOIN " + join[i].table + " ON "
                    + joinConditions.join(" AND ");
            }

            var fieldsString = fields && fields.length > 0 ? fields.join(", ") : "*";
            var statement = "SELECT " + fieldsString + " FROM " + table + joinString + whereString;
            return this.sql(statement, whereValues, mapResults);
        };

        this.sqlInsert = function (table, fields) {
            var fieldsKeys = [];
            var fieldsValues = [];
            var valuesString = "";
            for (var key in fields) {
                fieldsKeys.push(key);
                fieldsValues.push(fields[key]);
                if (valuesString.length > 0) {
                    valuesString += ", ";
                }
                valuesString += "?";
            }
            var statement = "INSERT INTO " + table + " (" + fieldsKeys.join(", ") + ") VALUES ("
                + valuesString + ")";
            return this.sql(statement, fieldsValues);
        };

        this.sqlDrop = function (table) {
            var statement = "DROP TABLE IF EXISTS " + table;
            return this.sql(statement, []);
        };

    },

    addTracks: function (params) {
        var that = this;
        var id = params.id;
        var tracks = params.tracks;

        var cachedAlbumArtists = {},
            cachedArtists = {},
            cachedAlbums = {},
            cachedArtistIds = {},
            cachedAlbumIds = {};

        var t = new Hatchet.Collection.Transaction(this, id);
        return t.beginTransaction().then(function () {
            // First we insert all artists and albumArtists
            t.sqlInsert("artists", {
                artist: "Various Artists",
                artistDisambiguation: ""
            });
            for (var i = 0; i < tracks.length; i++) {
                tracks[i].track = tracks[i].track || "";
                tracks[i].album = tracks[i].album || "";
                tracks[i].artist = tracks[i].artist || "";
                tracks[i].artistDisambiguation = tracks[i].artistDisambiguation || "";
                tracks[i].albumArtist = tracks[i].albumArtist || "";
                tracks[i].albumArtistDisambiguation = tracks[i].albumArtistDisambiguation || "";
                (function (track) {
                    t.sqlInsert("artists", {
                        artist: track.artist,
                        artistDisambiguation: track.artistDisambiguation
                    });
                    t.sqlInsert("albumArtists", {
                        albumArtist: track.albumArtist,
                        albumArtistDisambiguation: track.albumArtistDisambiguation
                    });
                })(tracks[i]);
            }
            return t.execDeferredStatements();
        }).then(function () {
            // Get all artists' and albumArtists' db ids
            t.sqlSelect("albumArtists", function (r) {
                return {
                    albumArtist: r.albumArtist,
                    albumArtistDisambiguation: r.albumArtistDisambiguation,
                    _id: r._id
                };
            });
            t.sqlSelect("artists", function (r) {
                return {
                    artist: r.artist,
                    artistDisambiguation: r.artistDisambiguation,
                    _id: r._id
                };
            });
            return t.execDeferredStatements();
        }).then(function (resultsArray) {
            // Store the db ids in a map
            var i, row, albumArtists = {};
            for (i = 0; i < resultsArray[0].length; i++) {
                row = resultsArray[0][i];
                albumArtists[row.albumArtist + "♣" + row.albumArtistDisambiguation] = row._id;
            }
            for (i = 0; i < resultsArray[1].length; i++) {
                row = resultsArray[1][i];
                cachedArtists[row.artist + "♣" + row.artistDisambiguation] = row._id;
                cachedArtistIds[row._id] = {
                    artist: row.artist,
                    artistDisambiguation: row.artistDisambiguation
                };
            }

            for (i = 0; i < tracks.length; i++) {
                var track = tracks[i];
                var album = cachedAlbumArtists[track.album];
                if (!album) {
                    album = cachedAlbumArtists[track.album] = {
                        artists: {}
                    };
                }
                album.artists[track.artist] = true;
                var artistCount = Object.keys(album.artists).length;
                if (artistCount == 1) {
                    album.albumArtistId =
                        cachedArtists[track.artist + "♣" + track.artistDisambiguation];
                } else if (artistCount == 2) {
                    album.albumArtistId = cachedArtists["Various Artists♣"];
                }
            }
        }).then(function () {
            // Insert all albums
            for (var i = 0; i < tracks.length; i++) {
                (function (track) {
                    var albumArtistId = cachedAlbumArtists[track.album].albumArtistId;
                    t.sqlInsert("albums", {
                        album: track.album,
                        albumArtistId: albumArtistId
                    });
                })(tracks[i]);
            }
            return t.execDeferredStatements();
        }).then(function () {
            // Get the albums' db ids
            t.sqlSelect("albums", function (r) {
                return {
                    album: r.album,
                    albumArtistId: r.albumArtistId,
                    _id: r._id
                };
            });
            return t.execDeferredStatements();
        }).then(function (results) {
            // Store the db ids in a map
            results = results[0];
            for (var i = 0; i < results.length; i++) {
                var row = results[i];
                cachedAlbums[row.album + "♣" + row.albumArtistId] = row._id;
                cachedAlbumIds[row._id] = {
                    album: row.album,
                    albumArtistId: row.albumArtistId
                };
            }
        }).then(function () {
            // Now we are ready to insert the tracks
            for (var i = 0; i < tracks.length; i++) {
                (function (track) {
                    // Get all relevant ids that we stored in the previous steps
                    var artistId = cachedArtists[track.artist + "♣" + track.artistDisambiguation];
                    var albumArtistId = cachedAlbumArtists[track.album].albumArtistId;
                    var albumId = cachedAlbums[track.album + "♣" + albumArtistId];
                    // Insert the artist <=> album relations
                    t.sqlInsert("artistAlbums", {
                        albumId: albumId,
                        artistId: artistId
                    });
                    // Insert the tracks
                    t.sqlInsert("tracks", {
                        track: track.track,
                        artistId: artistId,
                        albumId: albumId,
                        url: track.url,
                        duration: track.duration,
                        linkUrl: track.linkUrl,
                        releaseyear: track.releaseyear,
                        bitrate: track.bitrate,
                        albumPos: track.albumpos
                    });
                })(tracks[i]);
            }
            return t.execDeferredStatements();
        }).then(function () {
            var resultMap = function (r) {
                return {
                    _id: r._id,
                    artistId: r.artistId,
                    albumId: r.albumId,
                    track: r.track
                };
            };
            // Get the tracks' db ids
            t.sqlSelect("tracks", resultMap, ["_id", "artistId", "albumId", "track"]);
            return t.execDeferredStatements();
        }).then(function (results) {
            that._trackCount = results[0].length;
            Hatchet.log("Added " + results[0].length + " tracks to collection '" + id + "'");
            // Add the db ids together with the basic metadata to the fuzzy index list
            var fuzzyIndexList = [];
            for (var i = 0; i < results[0].length; i++) {
                var row = results[0][i];
                fuzzyIndexList.push({
                    id: row._id,
                    artist: cachedArtistIds[row.artistId].artist,
                    album: cachedAlbumIds[row.albumId].album,
                    track: row.track
                });
            }
            Hatchet.createFuzzyIndex(fuzzyIndexList);
        });
    },

    wipe: function (params) {
        var id = params.id;

        var that = this;

        var t = new Hatchet.Collection.Transaction(this, id);
        return t.beginTransaction().then(function () {
            t.sqlDrop("artists");
            t.sqlDrop("albumArtists");
            t.sqlDrop("albums");
            t.sqlDrop("artistAlbums");
            t.sqlDrop("tracks");
            return t.execDeferredStatements();
        }).then(function () {
            return new RSVP.Promise(function (resolve, reject) {
                that.cachedDbs[id].changeVersion(that.cachedDbs[id].version, "", null,
                    function (err) {
                        Hatchet.error("Error trying to change db version!", err);
                        reject();
                    }, function () {
                        delete that.cachedDbs[id];
                        Hatchet.deleteFuzzyIndex(id);
                        Hatchet.log("Wiped collection '" + id + "'");
                        resolve();
                    });
            });
        });
    },

    revision: function (params) {
        return RSVP.resolve();
    },

    _fuzzyIndexIdsToTracks: function (resultIds, id) {
        if (typeof id === 'undefined') {
            id = this.settings.id;
        }
        var t = new Hatchet.Collection.Transaction(this, id);
        return t.beginTransaction().then(function () {
            var mapFn = function (row) {
                return {
                    artist: row.artist,
                    artistDisambiguation: row.artistDisambiguation,
                    album: row.album,
                    track: row.track,
                    duration: row.duration,
                    url: row.url,
                    linkUrl: row.linkUrl,
                    releaseyear: row.releaseyear,
                    bitrate: row.bitrate,
                    albumpos: row.albumPos
                };
            };
            for (var idx = 0; resultIds && idx < resultIds.length; idx++) {
                var trackid = resultIds[idx][0];
                var where = {_id: trackid};
                t.sqlSelect("tracks", mapFn,
                    [],
                    where, [
                        {
                            table: "artists",
                            conditions: {
                                artistId: "_id"
                            }
                        }, {
                            table: "albums",
                            conditions: {
                                albumId: "_id"
                            }
                        }
                    ]
                );
            }
            return t.execDeferredStatements();
        }).then(function (results) {
            var merged = [];
            return merged.concat.apply(merged,
                results.map(function (e) {
                    //every result has one track
                    return e[0];
                }));
        });
    },

    _adapter_resolve: function (params) {
        return RSVP.Promise.resolve(this.resolve(params)).then(function (results) {
            return {
                'tracks': results
            };
        });
    },

    resolve: function (params) {
        var resultIds = Hatchet.resolveFromFuzzyIndex(params.artist, params.album, params.track);
        return this._fuzzyIndexIdsToTracks(resultIds);
    },

    search: function (params) {
        var resultIds = Hatchet.searchFuzzyIndex(params.query);

        return this._fuzzyIndexIdsToTracks(resultIds).then(function(tracks) {
            return {
                tracks: tracks
            };
        });
    },

    tracks: function (params, where) {
        //TODO filter/where support
        var id = params.id;
        if (typeof id === 'undefined') {
            id = this.settings.id;
        }

        var t = new Hatchet.Collection.Transaction(this, id);
        return t.beginTransaction().then(function () {
            var mapFn = function (row) {
                return {
                    artist: row.artist,
                    artistDisambiguation: row.artistDisambiguation,
                    album: row.album,
                    track: row.track,
                    duration: row.duration,
                    url: row.url,
                    linkUrl: row.linkUrl,
                    releaseyear: row.releaseyear,
                    bitrate: row.bitrate,
                    albumpos: row.albumPos
                };
            };
            t.sqlSelect("tracks", mapFn,
                [],
                where, [
                    {
                        table: "artists",
                        conditions: {
                            artistId: "_id"
                        }
                    }, {
                        table: "albums",
                        conditions: {
                            albumId: "_id"
                        }
                    }
                ]
            );
            return t.execDeferredStatements();
        }).then(function (results) {
            return {tracks: results[0]};
        });
    },

    albums: function (params, where) {
        //TODO filter/where support
        var id = params.id;
        if (typeof id === 'undefined') {
            id = this.settings.id;
        }

        var t = new Hatchet.Collection.Transaction(this, id);
        return t.beginTransaction().then(function () {
            var mapFn = function (row) {
                return {
                    albumArtist: row.artist,
                    albumArtistDisambiguation: row.artistDisambiguation,
                    album: row.album
                };
            };
            t.sqlSelect("albums", mapFn,
                ["album", "artist", "artistDisambiguation"],
                where, [
                    {
                        table: "artists",
                        conditions: {
                            albumArtistId: "_id"
                        }
                    }
                ]
            );
            return t.execDeferredStatements();
        }).then(function (results) {
            results = results[0].filter(function (e) {
                return (e.albumArtist != '' && e.album != '');
            });
            return {
                artists: results.map(function (i) {
                    return i.albumArtist;
                }),
                albums: results.map(function (i) {
                    return i.album;
                })
            };
        });
    },

    artists: function (params) {
        //TODO filter/where support
        var id = params.id;
        if (typeof id === 'undefined') {
            id = this.settings.id;
        }

        var t = new Hatchet.Collection.Transaction(this, id);
        return t.beginTransaction().then(function () {
            var mapFn = function (r) {
                return r.artist;
            };
            t.sqlSelect("artists", mapFn, ["artist", "artistDisambiguation"]);
            return t.execDeferredStatements();
        }).then(function (artists) {
            return {artists: artists[0]};
        });
    },

    //TODO: not exactly sure how is this one supposed to work
    //albumArtists: function (params) {
    //var id = params.id;

    //var t = new Hatchet.Collection.Transaction(this, id);
    //return t.beginTransaction().then(function () {
    //var mapFn = function(row) {
    //return {
    //albumArtist: row.albumArtist,
    //albumArtistDisambiguation: row.albumArtistDisambiguation
    //};
    //};
    //t.sqlSelect("albumArtists", ["albumArtist", "albumArtistDisambiguation"]);
    //return t.execDeferredStatements();
    //}).then(function (results) {
    //return results[0];
    //});
    //},

    artistAlbums: function (params) {
        //TODO filter/where support
        var id = params.id;
        if (typeof id === 'undefined') {
            id = this.settings.id;
        }
        var artist = params.artist;
        //var artistDisambiguation = params.artistDisambiguation;

        var t = new Hatchet.Collection.Transaction(this, id);
        return t.beginTransaction().then(function () {

            t.sqlSelect("artists", function (r) {
                return r._id;
            }, ["_id"], {
                artist: artist
                //artistDisambiguation: artistDisambiguation
            });
            return t.execDeferredStatements();
        }).then(function (results) {
            var artistId = results[0][0];
            t.sqlSelect("artistAlbums", function (r) {
                return r.album;
            }, ["albumId", 'album'], {
                artistId: artistId
            }, [
                {
                    table: "albums",
                    conditions: {
                        albumId: "_id"
                    }
                }
            ]);
            return t.execDeferredStatements();
        }).then(function (results) {
            return {
                artist: artist,
                albums: results[0]
            };
        });
    },

    albumTracks: function (params) {
        //TODO filter/where support
        var id = params.id;
        if (typeof id === 'undefined') {
            id = this.settings.id;
        }
        var albumArtist = params.artist;
        //var albumArtistDisambiguation = params.albumArtistDisambiguation;
        var album = params.album;

        var that = this;

        var t = new Hatchet.Collection.Transaction(this, id);
        return t.beginTransaction().then(function () {
            t.sqlSelect("artists", function (r) {
                return r._id;
            }, ["_id"], {
                artist: albumArtist
                //artistDisambiguation: albumArtistDisambiguation
            });
            return t.execDeferredStatements();
        }).then(function (results) {
            var albumArtistId = results[0][0];
            t.sqlSelect("albums", function (r) {
                return r._id;
            }, ["_id"], {
                album: album,
                albumArtistId: albumArtistId
            });
            return t.execDeferredStatements();
        }).then(function (results) {
            var albumId = results[0][0];
            return that.tracks(params, {
                albumId: albumId
            });
        });
    },

    collection: function () {
        this.settings.trackcount = this._trackCount;
        if (!this.settings.description) {
            this.settings.description = this.settings.prettyname;
        }
        this.settings.capabilities = [Hatchet.Collection.BrowseCapability.Artists,
            Hatchet.Collection.BrowseCapability.Albums,
            Hatchet.Collection.BrowseCapability.Tracks];
        if (!this.settings.weight && this.resolver && this.resolver.settings.weight) {
            this.settings.weight = this.resolver.settings.weight;
        }
        return this.settings;
    },

    getStreamUrl: function(params) {
        if(this.resolver) {
          return this.resolver.getStreamUrl(params);
        }

        return params;
    },

    getDownloadUrl: function(params) {
        if(this.resolver) {
          return this.resolver.getDownloadUrl(params);
        }

        return params;
    }
};
