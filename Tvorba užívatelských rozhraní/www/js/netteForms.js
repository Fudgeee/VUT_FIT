/*! netteForms.js | (c) 2004 David Grudl (https://davidgrudl.com) */
(function(m,e){if(m.JSON)if("function"===typeof define&&define.amd)define(function(){return e(m)});else if("object"===typeof module&&"object"===typeof module.exports)module.exports=e(m);else{var v=!m.Nette||!m.Nette.noInit;m.Nette=e(m);v&&m.Nette.initOnLoad()}})("undefined"!==typeof window?window:this,function(m){var e={},v={},t={},y=new m.WeakMap;e.formErrors=[];e.version="3.3.0";e.invalidNumberMessage="Please enter a valid value.";e.onDocumentReady=function(a){"loading"!==document.readyState?
a.call(this):document.addEventListener("DOMContentLoaded",a)};e.getValue=function(a){var b;if(a){if(a.tagName){if("radio"===a.type){var c=a.form.elements;for(b=0;b<c.length;b++)if(c[b].name===a.name&&c[b].checked)return c[b].value;return null}if("file"===a.type)return a.files||a.value;if("select"===a.tagName.toLowerCase()){b=a.selectedIndex;c=a.options;var d=[];if("select-one"===a.type)return 0>b?null:c[b].value;for(b=0;b<c.length;b++)c[b].selected&&d.push(c[b].value);return d}if(a.name&&"[]"===a.name.substr(-2)){c=
a.form.elements[a.name].tagName?[a]:a.form.elements[a.name];d=[];for(b=0;b<c.length;b++)("checkbox"!==c[b].type||c[b].checked)&&d.push(c[b].value);return d}return"checkbox"===a.type?a.checked:"textarea"===a.tagName.toLowerCase()?a.value.replace("\r",""):a.value.replace("\r","").replace(/^\s+|\s+$/g,"")}return a[0]?e.getValue(a[0]):null}return null};e.getEffectiveValue=function(a,b){var c=e.getValue(a);a.getAttribute&&c===a.getAttribute("data-nette-empty-value")&&(c="");b&&void 0===v[a.name]&&(v[a.name]=
!0,b={value:c},e.validateControl(a,null,!0,b),c=b.value,delete v[a.name]);return c};e.validateControl=function(a,b,c,d,f){var g=!b;a=a.tagName?a:a[0];b=b||JSON.parse(a.getAttribute("data-nette-rules")||"[]");d=void 0===d?{value:e.getEffectiveValue(a)}:d;f=void 0===f?!e.validateRule(a,":filled",null,d):f;for(var n=0,r=b.length;n<r;n++){var h=b[n],p=h.op.match(/(~)?([^?]+)/),q=h.control?a.form.elements.namedItem(h.control):a;h.neg=p[1];h.op=p[2];h.condition=!!h.rules;if(q&&(!f||h.condition||":filled"===
h.op)&&(q=q.tagName?q:q[0],p=e.validateRule(q,h.op,h.arg,a===q?d:void 0),null!==p))if(h.neg&&(p=!p),h.condition&&p){if(!e.validateControl(a,h.rules,c,d,":blank"===h.op?!1:f))return!1}else if(!h.condition&&!p&&!e.isDisabled(q)){if(!c){var k=Array.isArray(h.arg)?h.arg:[h.arg];b=h.msg.replace(/%(value|\d+)/g,function(l,x){return e.getValue("value"===x?q:a.form.elements.namedItem(k[x].control))});e.addError(q,b)}return!1}}return"number"!==a.type||a.validity.valid?!0:(g&&!c&&e.addError(a,e.invalidNumberMessage),
!1)};e.validateForm=function(a,b){a=a.form||a;var c=!1;e.formErrors=[];if(a["nette-submittedBy"]&&null!==a["nette-submittedBy"].getAttribute("formnovalidate"))if(c=JSON.parse(a["nette-submittedBy"].getAttribute("data-nette-validation-scope")||"[]"),c.length)c=new RegExp("^("+c.join("-|")+"-)");else return e.showFormErrors(a,[]),!0;var d={},f;for(f=0;f<a.elements.length;f++){var g=a.elements[f];if(!g.tagName||g.tagName.toLowerCase()in{input:1,select:1,textarea:1,button:1}){if("radio"===g.type){if(d[g.name])continue;
d[g.name]=!0}if(!(c&&!g.name.replace(/]\[|\[|]|$/g,"-").match(c)||e.isDisabled(g)||e.validateControl(g,null,b)||e.formErrors.length))return!1}}b=!e.formErrors.length;e.showFormErrors(a,e.formErrors);return b};e.isDisabled=function(a){if("radio"===a.type){for(var b=0,c=a.form.elements;b<c.length;b++)if(c[b].name===a.name&&!c[b].disabled)return!1;return!0}return a.disabled};e.addError=function(a,b){e.formErrors.push({element:a,message:b})};e.showFormErrors=function(a,b){a=[];for(var c,d=0;d<b.length;d++){var f=
b[d].element,g=b[d].message;0>a.indexOf(g)&&(a.push(g),!c&&f.focus&&(c=f))}a.length&&e.showModal(a.join("\n"),function(){c&&c.focus()})};e.showModal=function(a,b){var c=document.createElement("dialog"),d=navigator.userAgentData;if(d&&c.showModal&&d.brands.some(function(n){return"Opera"===n.brand||"Chromium"===n.brand&&d.mobile})){var f=document.createElement("style");f.innerText=".netteFormsModal { text-align: center; margin: auto; border: 2px solid black; padding: 1rem } .netteFormsModal button { padding: .1em 2em }";
var g=document.createElement("button");g.innerText="OK";g.onclick=function(){c.remove();b()};c.setAttribute("class","netteFormsModal");c.innerText=a+"\n\n";c.appendChild(f);c.appendChild(g);document.body.appendChild(c);c.showModal()}else alert(a),b()};e.validateRule=function(a,b,c,d){d=void 0===d?{value:e.getEffectiveValue(a,!0)}:d;":"===b.charAt(0)&&(b=b.substr(1));b=b.replace("::","_");b=b.replace(/\\/g,"");for(var f=Array.isArray(c)?c.slice(0):[c],g=0,n=f.length;g<n;g++)if(f[g]&&f[g].control){var r=
a.form.elements.namedItem(f[g].control);f[g]=r===a?d.value:e.getEffectiveValue(r,!0)}return e.validators[b]?e.validators[b](a,Array.isArray(c)?f:f[0],d.value,d):null};e.validators={filled:function(a,b,c){return"number"===a.type&&a.validity.badInput?!0:""!==c&&!1!==c&&null!==c&&(!Array.isArray(c)||!!c.length)&&(!m.FileList||!(c instanceof m.FileList)||c.length)},blank:function(a,b,c){return!e.validators.filled(a,b,c)},valid:function(a){return e.validateControl(a,null,!0)},equal:function(a,b,c){if(void 0===
b)return null;a=function(r){return"number"===typeof r||"string"===typeof r?""+r:!0===r?"1":""};c=Array.isArray(c)?c:[c];b=Array.isArray(b)?b:[b];var d=0,f=c.length;a:for(;d<f;d++){for(var g=0,n=b.length;g<n;g++)if(a(c[d])===a(b[g]))continue a;return!1}return 0<c.length},notEqual:function(a,b,c){return void 0===b?null:!e.validators.equal(a,b,c)},minLength:function(a,b,c){if("number"===a.type){if(a.validity.tooShort)return!1;if(a.validity.badInput)return null}return c.length>=b},maxLength:function(a,
b,c){if("number"===a.type){if(a.validity.tooLong)return!1;if(a.validity.badInput)return null}return c.length<=b},length:function(a,b,c){if("number"===a.type){if(a.validity.tooShort||a.validity.tooLong)return!1;if(a.validity.badInput)return null}b=Array.isArray(b)?b:[b,b];return(null===b[0]||c.length>=b[0])&&(null===b[1]||c.length<=b[1])},email:function(a,b,c){return/^("([ !#-[\]-~]|\\[ -~])+"|[-a-z0-9!#$%&'*+/=?^_`{|}~]+(\.[-a-z0-9!#$%&'*+/=?^_`{|}~]+)*)@([0-9a-z\u00C0-\u02FF\u0370-\u1EFF]([-0-9a-z\u00C0-\u02FF\u0370-\u1EFF]{0,61}[0-9a-z\u00C0-\u02FF\u0370-\u1EFF])?\.)+[a-z\u00C0-\u02FF\u0370-\u1EFF]([-0-9a-z\u00C0-\u02FF\u0370-\u1EFF]{0,17}[a-z\u00C0-\u02FF\u0370-\u1EFF])?$/i.test(c)},
url:function(a,b,c,d){/^[a-z\d+.-]+:/.test(c)||(c="https://"+c);return/^https?:\/\/((([-_0-9a-z\u00C0-\u02FF\u0370-\u1EFF]+\.)*[0-9a-z\u00C0-\u02FF\u0370-\u1EFF]([-0-9a-z\u00C0-\u02FF\u0370-\u1EFF]{0,61}[0-9a-z\u00C0-\u02FF\u0370-\u1EFF])?\.)?[a-z\u00C0-\u02FF\u0370-\u1EFF]([-0-9a-z\u00C0-\u02FF\u0370-\u1EFF]{0,17}[a-z\u00C0-\u02FF\u0370-\u1EFF])?|\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}|\[[0-9a-f:]{3,39}\])(:\d{1,5})?(\/\S*)?$/i.test(c)?(d.value=c,!0):!1},regexp:function(a,b,c){a="string"===typeof b?b.match(/^\/(.*)\/([imu]*)$/):
!1;try{return a&&(new RegExp(a[1],a[2].replace("u",""))).test(c)}catch(d){}},pattern:function(a,b,c,d,f){if("string"!==typeof b)return null;try{try{var g=new RegExp("^(?:"+b+")$",f?"ui":"u")}catch(n){g=new RegExp("^(?:"+b+")$",f?"i":"")}if(m.FileList&&c instanceof FileList){for(a=0;a<c.length;a++)if(!g.test(c[a].name))return!1;return!0}return g.test(c)}catch(n){}},patternCaseInsensitive:function(a,b,c){return e.validators.pattern(a,b,c,null,!0)},numeric:function(a,b,c){return"number"===a.type&&a.validity.badInput?
!1:/^[0-9]+$/.test(c)},integer:function(a,b,c){return"number"===a.type&&a.validity.badInput?!1:/^-?[0-9]+$/.test(c)},"float":function(a,b,c,d){if("number"===a.type&&a.validity.badInput)return!1;c=c.replace(/ +/g,"").replace(/,/g,".");return/^-?[0-9]*\.?[0-9]+$/.test(c)?(d.value=c,!0):!1},min:function(a,b,c){if("number"===a.type){if(a.validity.rangeUnderflow)return!1;if(a.validity.badInput)return null}return null===b||parseFloat(c)>=b},max:function(a,b,c){if("number"===a.type){if(a.validity.rangeOverflow)return!1;
if(a.validity.badInput)return null}return null===b||parseFloat(c)<=b},range:function(a,b,c){if("number"===a.type){if(a.validity.rangeUnderflow||a.validity.rangeOverflow)return!1;if(a.validity.badInput)return null}return Array.isArray(b)?(null===b[0]||parseFloat(c)>=b[0])&&(null===b[1]||parseFloat(c)<=b[1]):null},submitted:function(a){return a.form["nette-submittedBy"]===a},fileSize:function(a,b,c){if(m.FileList)for(a=0;a<c.length;a++)if(c[a].size>b)return!1;return!0},mimeType:function(a,b,c){b=Array.isArray(b)?
b:[b];for(var d=0,f=b.length,g=[];d<f;d++)g.push("^"+b[d].replace(/([^\w])/g,"\\$1").replace("\\*",".*")+"$");g=new RegExp(g.join("|"));if(m.FileList&&c instanceof FileList)for(d=0;d<c.length;d++){if(c[d].type&&!g.test(c[d].type))return!1;if(a.validity.badInput)return null}return!0},image:function(a,b,c){return e.validators.mimeType(a,["image/gif","image/png","image/jpeg","image/webp"],c)},"static":function(a,b){return b}};e.toggleForm=function(a,b){var c;t={};for(c=0;c<a.elements.length;c++)a.elements[c].tagName.toLowerCase()in
{input:1,select:1,textarea:1,button:1}&&e.toggleControl(a.elements[c],null,null,!b);for(c in t)e.toggle(c,t[c].state,t[c].elem,b)};e.toggleControl=function(a,b,c,d,f,g){b=b||JSON.parse(a.getAttribute("data-nette-rules")||"[]");f=void 0===f?{value:e.getEffectiveValue(a)}:f;g=void 0===g?!e.validateRule(a,":filled",null,f):g;for(var n=!1,r=function(z){e.toggleForm(a.form,z)},h,p=0,q=b.length;p<q;p++){var k=b[p];h=k.op.match(/(~)?([^?]+)/);var l=k.control?a.form.elements.namedItem(k.control):a;k.neg=
h[1];k.op=h[2];k.condition=!!k.rules;if(l&&(!g||k.condition||":filled"===k.op)){h=c;if(!1!==c){h=e.validateRule(l,k.op,k.arg,a===l?f:void 0);if(null===h)continue;else k.neg&&(h=!h);k.condition||(c=h)}if(k.condition&&e.toggleControl(a,k.rules,h,d,f,":blank"===k.op?!1:g)||k.toggle){n=!0;if(d){var x=l.tagName?l.name:l[0].name;l=l.tagName?l.form.elements:l;for(var u=0;u<l.length;u++)l[u].name!==x||y.has(l[u])||(l[u].addEventListener("change",r),y.set(l[u],null))}for(var w in k.toggle||[])t[w]=t[w]||{elem:a},
t[w].state=t[w].state||(k.toggle[w]?h:!h)}}}return n};e.toggle=function(a,b,c,d){/^\w[\w.:-]*$/.test(a)&&(a="#"+a);a=document.querySelectorAll(a);for(c=0;c<a.length;c++)a[c].hidden=!b};e.compactCheckboxes=function(a){var b,c={};for(b=0;b<a.elements.length;b++){var d=a.elements[b];if(d.tagName&&"input"===d.tagName.toLowerCase()&&"checkbox"===d.type){if(d.name&&"[]"===d.name.substr(-2)){var f=d.name.substr(0,d.name.length-2);d.removeAttribute("name");d.setAttribute("data-nette-name",f)}if(f=d.getAttribute("data-nette-name"))c[f]=
c[f]||[],d.checked&&!d.disabled&&c[f].push(d.value)}}for(f in c)void 0===a.elements[f]&&(d=document.createElement("input"),d.setAttribute("name",f),d.setAttribute("type","hidden"),a.appendChild(d)),a.elements[f].value=c[f].join(","),a.elements[f].disabled=0===c[f].length};e.initForm=function(a){"get"===a.method&&a.hasAttribute("data-nette-compact")&&a.addEventListener("submit",function(){e.compactCheckboxes(a)});a:{for(var b=0;b<a.elements.length;b++)if(a.elements[b].getAttribute("data-nette-rules"))break a;
return}e.toggleForm(a);a.noValidate||(a.noValidate=!0,a.addEventListener("submit",function(c){e.validateForm(a)||(c.stopPropagation(),c.preventDefault())}))};e.initOnLoad=function(){e.onDocumentReady(function(){for(var a=0;a<document.forms.length;a++)e.initForm(document.forms[a]);document.body.addEventListener("click",function(b){for(b=b.target;b;){if(b.form&&b.type in{submit:1,image:1}){b.form["nette-submittedBy"]=b;break}b=b.parentNode}})})};e.webalize=function(a){a=a.toLowerCase();var b="",c;for(c=
0;c<a.length;c++){var d=e.webalizeTable[a.charAt(c)];b+=d?d:a.charAt(c)}return b.replace(/[^a-z0-9]+/g,"-").replace(/^-|-$/g,"")};e.webalizeTable={"\u00e1":"a","\u00e4":"a","\u010d":"c","\u010f":"d","\u00e9":"e","\u011b":"e","\u00ed":"i","\u013e":"l","\u0148":"n","\u00f3":"o","\u00f4":"o","\u0159":"r","\u0161":"s","\u0165":"t","\u00fa":"u","\u016f":"u","\u00fd":"y","\u017e":"z"};return e});