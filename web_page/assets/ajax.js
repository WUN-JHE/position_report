function ajax(option) {
    if (!option.url) {
        return;
    }
    var type = option.type || "GET"; //判斷option.type會不會回傳true如果會的話 type為option.type 否則為GET 為POST or GET 
    var callback = option.callback || function() {}; //同上 option.callback為true得話 type為option.callback 否則為function(){}
    var header = option.header || { 'Content-Type': 'application/x-www-form-urlencoded' };
    var xhr = new XMLHttpRequest();
    var body = null;
    var url = option.url;
    xhr.onreadystatechange = function() {
        callback.call(xhr, xhr); //判斷如果readystate變換的話執行 function
    }
    if (option.data) {
        if (type === "POST") {
            body = param(option.data); //預設參數
        } else {
            url = url + "?" + param(option.data) + "&time=" + new Date().getTime();
        }
    }

    xhr.open(type, url);
    for (var name in header) {
        xhr.setRequestHeader(name, header[name]);
    }
    xhr.send(body);
}

function param(obj) {
    var pairs = [],
        pair;
    for (var name in obj) {
        pair = encodeURIComponent(name) + "=" + encodeURIComponent(obj[name]);
        pairs.push(pair);
    }
    return pairs.join('&');
}

export { ajax };