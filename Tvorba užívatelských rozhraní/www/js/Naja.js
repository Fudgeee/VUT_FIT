!function(t,e){"object"==typeof exports&&"undefined"!=typeof module?module.exports=e():"function"==typeof define&&define.amd?define(e):(t="undefined"!=typeof globalThis?globalThis:t||self).naja=e()}(this,(function(){"use strict";var t="undefined"!=typeof globalThis?globalThis:"undefined"!=typeof window?window:"undefined"!=typeof global?global:"undefined"!=typeof self?self:{};function e(t,e,...i){if(!t)throw new TypeError(n(e,i))}function n(t,e){let n=0;return t.replace(/%[os]/gu,(()=>i(e[n++])))}function i(t){return"object"!=typeof t||null===t?String(t):Object.prototype.toString.call(t)}!function(){function e(t,e){if(!(t instanceof e))throw new TypeError("Cannot call a class as a function")}function n(t,e){for(var n=0;n<e.length;n++){var i=e[n];i.enumerable=i.enumerable||!1,i.configurable=!0,"value"in i&&(i.writable=!0),Object.defineProperty(t,i.key,i)}}function i(t,e,i){return e&&n(t.prototype,e),i&&n(t,i),t}function r(t,e){if("function"!=typeof e&&null!==e)throw new TypeError("Super expression must either be null or a function");t.prototype=Object.create(e&&e.prototype,{constructor:{value:t,writable:!0,configurable:!0}}),e&&a(t,e)}function o(t){return o=Object.setPrototypeOf?Object.getPrototypeOf:function(t){return t.__proto__||Object.getPrototypeOf(t)},o(t)}function a(t,e){return a=Object.setPrototypeOf||function(t,e){return t.__proto__=e,t},a(t,e)}function s(){if("undefined"==typeof Reflect||!Reflect.construct)return!1;if(Reflect.construct.sham)return!1;if("function"==typeof Proxy)return!0;try{return Boolean.prototype.valueOf.call(Reflect.construct(Boolean,[],(function(){}))),!0}catch(t){return!1}}function l(t){if(void 0===t)throw new ReferenceError("this hasn't been initialised - super() hasn't been called");return t}function c(t,e){return!e||"object"!=typeof e&&"function"!=typeof e?l(t):e}function u(t){var e=s();return function(){var n,i=o(t);if(e){var r=o(this).constructor;n=Reflect.construct(i,arguments,r)}else n=i.apply(this,arguments);return c(this,n)}}function d(t,e){for(;!Object.prototype.hasOwnProperty.call(t,e)&&null!==(t=o(t)););return t}function p(t,e,n){return p="undefined"!=typeof Reflect&&Reflect.get?Reflect.get:function(t,e,n){var i=d(t,e);if(i){var r=Object.getOwnPropertyDescriptor(i,e);return r.get?r.get.call(n):r.value}},p(t,e,n||t)}var h=function(){function t(){e(this,t),Object.defineProperty(this,"listeners",{value:{},writable:!0,configurable:!0})}return i(t,[{key:"addEventListener",value:function(t,e,n){t in this.listeners||(this.listeners[t]=[]),this.listeners[t].push({callback:e,options:n})}},{key:"removeEventListener",value:function(t,e){if(t in this.listeners)for(var n=this.listeners[t],i=0,r=n.length;i<r;i++)if(n[i].callback===e)return void n.splice(i,1)}},{key:"dispatchEvent",value:function(t){if(t.type in this.listeners){for(var e=this.listeners[t.type].slice(),n=0,i=e.length;n<i;n++){var r=e[n];try{r.callback.call(this,t)}catch(t){Promise.resolve().then((function(){throw t}))}r.options&&r.options.once&&this.removeEventListener(t.type,r.callback)}return!t.defaultPrevented}}}]),t}(),f=function(t){r(a,t);var n=u(a);function a(){var t;return e(this,a),(t=n.call(this)).listeners||h.call(l(t)),Object.defineProperty(l(t),"aborted",{value:!1,writable:!0,configurable:!0}),Object.defineProperty(l(t),"onabort",{value:null,writable:!0,configurable:!0}),t}return i(a,[{key:"toString",value:function(){return"[object AbortSignal]"}},{key:"dispatchEvent",value:function(t){"abort"===t.type&&(this.aborted=!0,"function"==typeof this.onabort&&this.onabort.call(this,t)),p(o(a.prototype),"dispatchEvent",this).call(this,t)}}]),a}(h),b=function(){function t(){e(this,t),Object.defineProperty(this,"signal",{value:new f,writable:!0,configurable:!0})}return i(t,[{key:"abort",value:function(){var t;try{t=new Event("abort")}catch(e){"undefined"!=typeof document?document.createEvent?(t=document.createEvent("Event")).initEvent("abort",!1,!1):(t=document.createEventObject()).type="abort":t={type:"abort",bubbles:!1,cancelable:!1}}this.signal.dispatchEvent(t)}},{key:"toString",value:function(){return"[object AbortController]"}}]),t}();function g(t){return t.__FORCE_INSTALL_ABORTCONTROLLER_POLYFILL?(console.log("__FORCE_INSTALL_ABORTCONTROLLER_POLYFILL=true is set, will force install polyfill"),!0):"function"==typeof t.Request&&!t.Request.prototype.hasOwnProperty("signal")||!t.AbortController}function v(t){"function"==typeof t&&(t={fetch:t});var e=t,n=e.fetch,i=e.Request,r=void 0===i?n.Request:i,o=e.AbortController,a=e.__FORCE_INSTALL_ABORTCONTROLLER_POLYFILL,s=void 0!==a&&a;if(!g({fetch:n,Request:r,AbortController:o,__FORCE_INSTALL_ABORTCONTROLLER_POLYFILL:s}))return{fetch:n,Request:l};var l=r;(l&&!l.prototype.hasOwnProperty("signal")||s)&&((l=function(t,e){var n;e&&e.signal&&(n=e.signal,delete e.signal);var i=new r(t,e);return n&&Object.defineProperty(i,"signal",{writable:!1,enumerable:!1,configurable:!0,value:n}),i}).prototype=r.prototype);var c=n;return{fetch:function(t,e){var n=l&&l.prototype.isPrototypeOf(t)?t.signal:e?e.signal:void 0;if(n){var i;try{i=new DOMException("Aborted","AbortError")}catch(t){(i=new Error("Aborted")).name="AbortError"}if(n.aborted)return Promise.reject(i);var r=new Promise((function(t,e){n.addEventListener("abort",(function(){return e(i)}),{once:!0})}));return e&&e.signal&&delete e.signal,Promise.race([r,c(t,e)])}return c(t,e)},Request:l}}"undefined"!=typeof Symbol&&Symbol.toStringTag&&(b.prototype[Symbol.toStringTag]="AbortController",f.prototype[Symbol.toStringTag]="AbortSignal"),function(t){if(g(t))if(t.fetch){var e=v(t),n=e.fetch,i=e.Request;t.fetch=n,t.Request=i,Object.defineProperty(t,"AbortController",{writable:!0,enumerable:!1,configurable:!0,value:b}),Object.defineProperty(t,"AbortSignal",{writable:!0,enumerable:!1,configurable:!0,value:f})}else console.warn("fetch() is not available, cannot install abortcontroller-polyfill")}("undefined"!=typeof self?self:t)}();const r="undefined"!=typeof window?window:"undefined"!=typeof self?self:"undefined"!=typeof global?global:"undefined"!=typeof globalThis?globalThis:void 0;class o{constructor(t,e){this.code=t,this.message=e}warn(...t){var e;try{undefined;const n=(null!==(e=(new Error).stack)&&void 0!==e?e:"").replace(/^(?:.+?\n){2}/gu,"\n");console.warn(this.message,...t,n)}catch(t){}}}const a=new o("W01","Unable to initialize event under dispatching."),s=new o("W02","Assigning any falsy value to 'cancelBubble' property has no effect."),l=new o("W03","Assigning any truthy value to 'returnValue' property has no effect."),c=new o("W04","Unable to preventDefault on non-cancelable events."),u=new o("W05","Unable to preventDefault inside passive event listener invocation."),d=new o("W06","An event listener wasn't added because it has been added already: %o, %o"),p=new o("W07","The %o option value was abandoned because the event listener wasn't added as duplicated."),h=new o("W08","The 'callback' argument must be a function or an object that has 'handleEvent' method: %o");new o("W09","Event attribute handler must be a function: %o");class f{static get NONE(){return b}static get CAPTURING_PHASE(){return g}static get AT_TARGET(){return v}static get BUBBLING_PHASE(){return m}constructor(t,e){Object.defineProperty(this,"isTrusted",{value:!1,enumerable:!0});const n=null!=e?e:{};y.set(this,{type:String(t),bubbles:Boolean(n.bubbles),cancelable:Boolean(n.cancelable),composed:Boolean(n.composed),target:null,currentTarget:null,stopPropagationFlag:!1,stopImmediatePropagationFlag:!1,canceledFlag:!1,inPassiveListenerFlag:!1,dispatchFlag:!1,timeStamp:Date.now()})}get type(){return E(this).type}get target(){return E(this).target}get srcElement(){return E(this).target}get currentTarget(){return E(this).currentTarget}composedPath(){const t=E(this).currentTarget;return t?[t]:[]}get NONE(){return b}get CAPTURING_PHASE(){return g}get AT_TARGET(){return v}get BUBBLING_PHASE(){return m}get eventPhase(){return E(this).dispatchFlag?2:0}stopPropagation(){E(this).stopPropagationFlag=!0}get cancelBubble(){return E(this).stopPropagationFlag}set cancelBubble(t){t?E(this).stopPropagationFlag=!0:s.warn()}stopImmediatePropagation(){const t=E(this);t.stopPropagationFlag=t.stopImmediatePropagationFlag=!0}get bubbles(){return E(this).bubbles}get cancelable(){return E(this).cancelable}get returnValue(){return!E(this).canceledFlag}set returnValue(t){t?l.warn():w(E(this))}preventDefault(){w(E(this))}get defaultPrevented(){return E(this).canceledFlag}get composed(){return E(this).composed}get isTrusted(){return!1}get timeStamp(){return E(this).timeStamp}initEvent(t,e=!1,n=!1){const i=E(this);i.dispatchFlag?a.warn():y.set(this,{...i,type:String(t),bubbles:Boolean(e),cancelable:Boolean(n),target:null,currentTarget:null,stopPropagationFlag:!1,stopImmediatePropagationFlag:!1,canceledFlag:!1})}}const b=0,g=1,v=2,m=3,y=new WeakMap;function E(t,n="this"){const i=y.get(t);return e(null!=i,"'%s' must be an object that Event constructor created, but got another one: %o",n,t),i}function w(t){t.inPassiveListenerFlag?u.warn():t.cancelable?t.canceledFlag=!0:c.warn()}Object.defineProperty(f,"NONE",{enumerable:!0}),Object.defineProperty(f,"CAPTURING_PHASE",{enumerable:!0}),Object.defineProperty(f,"AT_TARGET",{enumerable:!0}),Object.defineProperty(f,"BUBBLING_PHASE",{enumerable:!0});const O=Object.getOwnPropertyNames(f.prototype);for(let t=0;t<O.length;++t)"constructor"!==O[t]&&Object.defineProperty(f.prototype,O[t],{enumerable:!0});let A;void 0!==r&&void 0!==r.Event&&Object.setPrototypeOf(f.prototype,r.Event.prototype);const R={INDEX_SIZE_ERR:1,DOMSTRING_SIZE_ERR:2,HIERARCHY_REQUEST_ERR:3,WRONG_DOCUMENT_ERR:4,INVALID_CHARACTER_ERR:5,NO_DATA_ALLOWED_ERR:6,NO_MODIFICATION_ALLOWED_ERR:7,NOT_FOUND_ERR:8,NOT_SUPPORTED_ERR:9,INUSE_ATTRIBUTE_ERR:10,INVALID_STATE_ERR:11,SYNTAX_ERR:12,INVALID_MODIFICATION_ERR:13,NAMESPACE_ERR:14,INVALID_ACCESS_ERR:15,VALIDATION_ERR:16,TYPE_MISMATCH_ERR:17,SECURITY_ERR:18,NETWORK_ERR:19,ABORT_ERR:20,URL_MISMATCH_ERR:21,QUOTA_EXCEEDED_ERR:22,TIMEOUT_ERR:23,INVALID_NODE_TYPE_ERR:24,DATA_CLONE_ERR:25};function j(t){const e=Object.keys(R);for(let n=0;n<e.length;++n){const i=e[n],r=R[i];Object.defineProperty(t,i,{get:()=>r,configurable:!0,enumerable:!0})}}class S extends f{static wrap(t){return new(C(t))(t)}constructor(t){super(t.type,{bubbles:t.bubbles,cancelable:t.cancelable,composed:t.composed}),t.cancelBubble&&super.stopPropagation(),t.defaultPrevented&&super.preventDefault(),T.set(this,{original:t});const e=Object.keys(t);for(let n=0;n<e.length;++n){const i=e[n];i in this||Object.defineProperty(this,i,_(t,i))}}stopPropagation(){super.stopPropagation();const{original:t}=L(this);"stopPropagation"in t&&t.stopPropagation()}get cancelBubble(){return super.cancelBubble}set cancelBubble(t){super.cancelBubble=t;const{original:e}=L(this);"cancelBubble"in e&&(e.cancelBubble=t)}stopImmediatePropagation(){super.stopImmediatePropagation();const{original:t}=L(this);"stopImmediatePropagation"in t&&t.stopImmediatePropagation()}get returnValue(){return super.returnValue}set returnValue(t){super.returnValue=t;const{original:e}=L(this);"returnValue"in e&&(e.returnValue=t)}preventDefault(){super.preventDefault();const{original:t}=L(this);"preventDefault"in t&&t.preventDefault()}get timeStamp(){const{original:t}=L(this);return"timeStamp"in t?t.timeStamp:super.timeStamp}}const T=new WeakMap;function L(t){const n=T.get(t);return e(null!=n,"'this' is expected an Event object, but got",t),n}const P=new WeakMap;function C(t){const e=Object.getPrototypeOf(t);if(null==e)return S;let n=P.get(e);return null==n&&(n=function(t,e){class n extends t{}const i=Object.keys(e);for(let t=0;t<i.length;++t)Object.defineProperty(n.prototype,i[t],_(e,i[t]));return n}(C(e),e),P.set(e,n)),n}function _(t,e){const n=Object.getOwnPropertyDescriptor(t,e);return{get(){const t=L(this).original,n=t[e];return"function"==typeof n?n.bind(t):n},set(t){L(this).original[e]=t},configurable:n.configurable,enumerable:n.enumerable}}function I(t){return 1==(1&t.flags)}function N(t){return 2==(2&t.flags)}function k(t){return 4==(4&t.flags)}function F(t){return 8==(8&t.flags)}function H({callback:t},e,n){try{"function"==typeof t?t.call(e,n):"function"==typeof t.handleEvent&&t.handleEvent(n)}catch(t){!function(t){try{const e=t instanceof Error?t:new Error(i(t));if("function"==typeof dispatchEvent&&"function"==typeof ErrorEvent)dispatchEvent(new ErrorEvent("error",{error:e,message:e.message}));else if("undefined"!=typeof process&&"function"==typeof process.emit)return void process.emit("uncaughtException",e);console.error(e)}catch(t){}}(t)}}function U({listeners:t},e,n){for(let i=0;i<t.length;++i)if(t[i].callback===e&&I(t[i])===n)return i;return-1}function q(t,e,n){const i=U(t,e,n);return-1!==i&&D(t,i)}function D(t,e,n=!1){const i=t.listeners[e];return function(t){t.flags|=8}(i),i.signal&&i.signal.removeEventListener("abort",i.signalListener),t.cow&&!n?(t.cow=!1,t.listeners=t.listeners.filter(((t,n)=>n!==e)),!1):(t.listeners.splice(e,1),!0)}P.set(Object.prototype,S),void 0!==r&&void 0!==r.Event&&P.set(r.Event.prototype,S);class B{constructor(){M.set(this,Object.create(null))}addEventListener(t,e,n){const i=x(this),{callback:r,capture:o,once:a,passive:s,signal:l,type:c}=function(t,e,n){var i;if(z(e),"object"==typeof n&&null!==n)return{type:String(t),callback:null!=e?e:void 0,capture:Boolean(n.capture),passive:Boolean(n.passive),once:Boolean(n.once),signal:null!==(i=n.signal)&&void 0!==i?i:void 0};return{type:String(t),callback:null!=e?e:void 0,capture:Boolean(n),passive:!1,once:!1,signal:void 0}}(t,e,n);if(null==r||(null==l?void 0:l.aborted))return;const u=function(t,e){var n;return null!==(n=t[e])&&void 0!==n?n:t[e]={attrCallback:void 0,attrListener:void 0,cow:!1,listeners:[]}}(i,c),h=U(u,r,o);-1===h?function(t,e,n,i,r,o){let a;o&&(a=q.bind(null,t,e,n),o.addEventListener("abort",a));const s=function(t,e,n,i,r,o){return{callback:t,flags:(e?1:0)|(n?2:0)|(i?4:0),signal:r,signalListener:o}}(e,n,i,r,o,a);t.cow?(t.cow=!1,t.listeners=[...t.listeners,s]):t.listeners.push(s)}(u,r,o,s,a,l):function(t,e,n,i){d.warn(I(t)?"capture":"bubble",t.callback),N(t)!==e&&p.warn("passive");k(t)!==n&&p.warn("once");t.signal!==i&&p.warn("signal")}(u.listeners[h],s,a,l)}removeEventListener(t,e,n){const i=x(this),{callback:r,capture:o,type:a}=function(t,e,n){if(z(e),"object"==typeof n&&null!==n)return{type:String(t),callback:null!=e?e:void 0,capture:Boolean(n.capture)};return{type:String(t),callback:null!=e?e:void 0,capture:Boolean(n)}}(t,e,n),s=i[a];null!=r&&s&&q(s,r,o)}dispatchEvent(t){const e=x(this)[String(t.type)];if(null==e)return!0;const n=t instanceof f?t:S.wrap(t),i=E(n,"event");if(i.dispatchFlag)throw o="This event has been in dispatching.",r.DOMException?new r.DOMException(o,"InvalidStateError"):(null==A&&(A=class t extends Error{constructor(e){super(e),Error.captureStackTrace&&Error.captureStackTrace(this,t)}get code(){return 11}get name(){return"InvalidStateError"}},Object.defineProperties(A.prototype,{code:{enumerable:!0},name:{enumerable:!0}}),j(A),j(A.prototype)),new A(o));var o;if(i.dispatchFlag=!0,i.target=i.currentTarget=this,!i.stopPropagationFlag){const{cow:t,listeners:r}=e;e.cow=!0;for(let o=0;o<r.length;++o){const a=r[o];if(!F(a)&&(k(a)&&D(e,o,!t)&&(o-=1),i.inPassiveListenerFlag=N(a),H(a,this,n),i.inPassiveListenerFlag=!1,i.stopImmediatePropagationFlag))break}t||(e.cow=!1)}return i.target=null,i.currentTarget=null,i.stopImmediatePropagationFlag=!1,i.stopPropagationFlag=!1,i.dispatchFlag=!1,!i.canceledFlag}}const M=new WeakMap;function x(t,n="this"){const i=M.get(t);return e(null!=i,"'%s' must be an object that EventTarget constructor created, but got another one: %o",n,t),i}function z(t){if("function"!=typeof t&&("object"!=typeof t||null===t||"function"!=typeof t.handleEvent)){if(null!=t&&"object"!=typeof t)throw new TypeError(n(h.message,[t]));h.warn(t)}}const G=Object.getOwnPropertyNames(B.prototype);for(let t=0;t<G.length;++t)"constructor"!==G[t]&&Object.defineProperty(B.prototype,G[t],{enumerable:!0});void 0!==r&&void 0!==r.EventTarget&&Object.setPrototypeOf(B.prototype,r.EventTarget.prototype);try{new window.EventTarget}catch(t){window.EventTarget=B}const $=t=>{"loading"===document.readyState?document.addEventListener("DOMContentLoaded",t):t()};class W extends Error{}const V=(t,e)=>{if(!t){throw new W("Assertion failed"+(void 0!==e?`: ${e}`:"."))}};class Y extends EventTarget{constructor(t){super(),this.naja=t,this.selector=".ajax",this.allowedOrigins=[window.location.origin],this.handler=this.handleUI.bind(this),t.addEventListener("init",this.initialize.bind(this))}initialize(){$((()=>this.bindUI(window.document.body))),this.naja.snippetHandler.addEventListener("afterUpdate",(t=>{const{snippet:e}=t.detail;this.bindUI(e)}))}bindUI(t){const e=[`a${this.selector}`,`input[type="submit"]${this.selector}`,`input[type="image"]${this.selector}`,`button[type="submit"]${this.selector}`,`form${this.selector} input[type="submit"]`,`form${this.selector} input[type="image"]`,`form${this.selector} button[type="submit"]`].join(", "),n=t=>{t.removeEventListener("click",this.handler),t.addEventListener("click",this.handler)},i=t.querySelectorAll(e);for(let t=0;t<i.length;t++)n(i.item(t));t.matches(e)&&n(t);const r=t=>{t.removeEventListener("submit",this.handler),t.addEventListener("submit",this.handler)};t.matches(`form${this.selector}`)&&r(t);const o=t.querySelectorAll(`form${this.selector}`);for(let t=0;t<o.length;t++)r(o.item(t))}handleUI(t){const e=t;if(e.altKey||e.ctrlKey||e.shiftKey||e.metaKey||e.button)return;const n=t.currentTarget,i={},r=()=>{};"submit"===t.type?this.submitForm(n,i,t).catch(r):"click"===t.type&&this.clickElement(n,i,e).catch(r)}async clickElement(t,e={},n){var i,r,o,a,s,l;let c,u="GET",d="";if(!this.dispatchEvent(new CustomEvent("interaction",{cancelable:!0,detail:{element:t,originalEvent:n,options:e}})))return null==n||n.preventDefault(),{};if("A"===t.tagName)V(t instanceof HTMLAnchorElement),u="GET",d=t.href,c=null;else if("INPUT"===t.tagName||"BUTTON"===t.tagName){V(t instanceof HTMLInputElement||t instanceof HTMLButtonElement);const{form:e}=t;if(u=null!==(a=null!==(r=null===(i=t.getAttribute("formmethod"))||void 0===i?void 0:i.toUpperCase())&&void 0!==r?r:null===(o=null==e?void 0:e.getAttribute("method"))||void 0===o?void 0:o.toUpperCase())&&void 0!==a?a:"GET",d=null!==(l=null!==(s=t.getAttribute("formaction"))&&void 0!==s?s:null==e?void 0:e.getAttribute("action"))&&void 0!==l?l:window.location.pathname+window.location.search,c=new FormData(null!=e?e:void 0),"submit"===t.type&&""!==t.name)c.append(t.name,t.value||"");else if("image"===t.type){const e=t.getBoundingClientRect(),i=""!==t.name?`${t.name}.`:"";c.append(`${i}x`,Math.max(0,Math.floor(void 0!==n?n.pageX-e.left:0))),c.append(`${i}y`,Math.max(0,Math.floor(void 0!==n?n.pageY-e.top:0)))}}if(!this.isUrlAllowed(d))throw new Error(`Cannot dispatch async request, URL is not allowed: ${d}`);return null==n||n.preventDefault(),this.naja.makeRequest(u,d,c,e)}async submitForm(t,e={},n){var i,r,o;if(!this.dispatchEvent(new CustomEvent("interaction",{cancelable:!0,detail:{element:t,originalEvent:n,options:e}})))return null==n||n.preventDefault(),{};const a=null!==(r=null===(i=t.getAttribute("method"))||void 0===i?void 0:i.toUpperCase())&&void 0!==r?r:"GET",s=null!==(o=t.getAttribute("action"))&&void 0!==o?o:window.location.pathname+window.location.search,l=new FormData(t);if(!this.isUrlAllowed(s))throw new Error(`Cannot dispatch async request, URL is not allowed: ${s}`);return null==n||n.preventDefault(),this.naja.makeRequest(a,s,l,e)}isUrlAllowed(t){const e=new URL(t,location.href);return"null"!==e.origin&&this.allowedOrigins.includes(e.origin)}}class K{constructor(t){this.naja=t,t.addEventListener("init",this.initialize.bind(this)),t.uiHandler.addEventListener("interaction",this.processForm.bind(this))}initialize(){$((()=>this.initForms(window.document.body))),this.naja.snippetHandler.addEventListener("afterUpdate",(t=>{const{snippet:e}=t.detail;this.initForms(e)}))}initForms(t){const e=this.netteForms||window.Nette;if(e){"form"===t.tagName&&e.initForm(t);const n=t.querySelectorAll("form");for(let t=0;t<n.length;t++)e.initForm(n.item(t))}}processForm(t){const{element:e,originalEvent:n}=t.detail,i=e;void 0!==i.form&&null!==i.form&&(i.form["nette-submittedBy"]=e);const r=this.netteForms||window.Nette;"FORM"!==e.tagName&&!e.form||!r||r.validateForm(e)||(n&&(n.stopImmediatePropagation(),n.preventDefault()),t.preventDefault())}}class X extends EventTarget{constructor(t){super(),this.naja=t,t.uiHandler.addEventListener("interaction",(t=>{var e,n,i;const{element:r,options:o}=t.detail;if(r&&(r.hasAttribute("data-naja-force-redirect")||(null===(e=r.form)||void 0===e?void 0:e.hasAttribute("data-naja-force-redirect")))){const t=null!==(n=r.getAttribute("data-naja-force-redirect"))&&void 0!==n?n:null===(i=r.form)||void 0===i?void 0:i.getAttribute("data-naja-force-redirect");o.forceRedirect="off"!==t}})),t.addEventListener("success",(t=>{var e;const{payload:n,options:i}=t.detail;n.redirect&&(this.makeRedirect(n.redirect,null!==(e=i.forceRedirect)&&void 0!==e&&e,i),t.stopImmediatePropagation())})),this.locationAdapter={assign:t=>window.location.assign(t)}}makeRedirect(t,e,n={}){t instanceof URL&&(t=t.href);let i=e||!this.naja.uiHandler.isUrlAllowed(t);this.dispatchEvent(new CustomEvent("redirect",{cancelable:!0,detail:{url:t,isHardRedirect:i,setHardRedirect(t){i=!!t},options:n}}))&&(i?this.locationAdapter.assign(t):this.naja.makeRequest("GET",t,null,n))}}class Q extends EventTarget{constructor(t){super(),this.naja=t,this.op={replace:(t,e)=>{t.innerHTML=e},prepend:(t,e)=>t.insertAdjacentHTML("afterbegin",e),append:(t,e)=>t.insertAdjacentHTML("beforeend",e)},t.addEventListener("success",(t=>{const{options:e,payload:n}=t.detail;n.snippets&&this.updateSnippets(n.snippets,!1,e)}))}static findSnippets(t){var e;const n={},i=window.document.querySelectorAll('[id^="snippet-"]');for(let r=0;r<i.length;r++){const o=i.item(r);(null===(e=null==t?void 0:t(o))||void 0===e||e)&&(n[o.id]=o.innerHTML)}return n}updateSnippets(t,e=!1,n={}){Object.keys(t).forEach((i=>{const r=document.getElementById(i);r&&this.updateSnippet(r,t[i],e,n)}))}updateSnippet(t,e,n,i){let r=this.op.replace;!t.hasAttribute("data-naja-snippet-prepend")&&!t.hasAttribute("data-ajax-prepend")||n?!t.hasAttribute("data-naja-snippet-append")&&!t.hasAttribute("data-ajax-append")||n||(r=this.op.append):r=this.op.prepend;this.dispatchEvent(new CustomEvent("beforeUpdate",{cancelable:!0,detail:{snippet:t,content:e,fromCache:n,operation:r,changeOperation(t){r=t},options:i}}))&&("title"===t.tagName.toLowerCase()?document.title=e:r(t,e),this.dispatchEvent(new CustomEvent("afterUpdate",{cancelable:!0,detail:{snippet:t,content:e,fromCache:n,operation:r,options:i}})))}}class J extends EventTarget{constructor(t){super(),this.naja=t,this.href=null,this.popStateHandler=this.handlePopState.bind(this),t.addEventListener("init",this.initialize.bind(this)),t.addEventListener("before",this.saveUrl.bind(this)),t.addEventListener("success",this.pushNewState.bind(this)),t.uiHandler.addEventListener("interaction",this.configureMode.bind(this)),this.historyAdapter={replaceState:(t,e,n)=>window.history.replaceState(t,e,n),pushState:(t,e,n)=>window.history.pushState(t,e,n)}}set uiCache(t){console.warn("Naja: HistoryHandler.uiCache is deprecated, use options.snippetCache instead."),this.naja.defaultOptions.snippetCache=t}initialize(t){const{defaultOptions:e}=t.detail;window.addEventListener("popstate",this.popStateHandler),$((()=>this.historyAdapter.replaceState(this.buildState(window.location.href,e),window.document.title,window.location.href)))}handlePopState(t){const{state:e}=t;if(!e)return;const n=this.naja.prepareOptions();this.dispatchEvent(new CustomEvent("restoreState",{detail:{state:e,options:n}}))}saveUrl(t){const{url:e}=t.detail;this.href=e}configureMode(t){var e,n,i;const{element:r,options:o}=t.detail;if(r&&(r.hasAttribute("data-naja-history")||(null===(e=r.form)||void 0===e?void 0:e.hasAttribute("data-naja-history")))){const t=null!==(n=r.getAttribute("data-naja-history"))&&void 0!==n?n:null===(i=r.form)||void 0===i?void 0:i.getAttribute("data-naja-history");o.history=J.normalizeMode(t)}}static normalizeMode(t){return"off"!==t&&!1!==t&&("replace"!==t||"replace")}pushNewState(t){const{payload:e,options:n}=t.detail,i=J.normalizeMode(n.history);if(!1===i)return;e.postGet&&e.url&&(this.href=e.url);const r="replace"===i?"replaceState":"pushState";this.historyAdapter[r](this.buildState(this.href,n),window.document.title,this.href),this.href=null}buildState(t,e){const n={href:t};return this.dispatchEvent(new CustomEvent("buildState",{detail:{state:n,options:e}})),n}}class Z extends EventTarget{constructor(t){super(),this.naja=t,this.storages={off:new tt(t),history:new et,session:new nt},t.uiHandler.addEventListener("interaction",this.configureCache.bind(this)),t.historyHandler.addEventListener("buildState",this.buildHistoryState.bind(this)),t.historyHandler.addEventListener("restoreState",this.restoreHistoryState.bind(this))}resolveStorage(t){let e;return e=!0===t||void 0===t?"history":!1===t?"off":t,this.storages[e]}configureCache(t){var e,n,i,r,o,a,s;const{element:l,options:c}=t.detail;if(l&&(l.hasAttribute("data-naja-snippet-cache")||(null===(e=l.form)||void 0===e?void 0:e.hasAttribute("data-naja-snippet-cache"))||l.hasAttribute("data-naja-history-cache")||(null===(n=l.form)||void 0===n?void 0:n.hasAttribute("data-naja-history-cache")))){const t=null!==(a=null!==(o=null!==(i=l.getAttribute("data-naja-snippet-cache"))&&void 0!==i?i:null===(r=l.form)||void 0===r?void 0:r.getAttribute("data-naja-snippet-cache"))&&void 0!==o?o:l.getAttribute("data-naja-history-cache"))&&void 0!==a?a:null===(s=l.form)||void 0===s?void 0:s.getAttribute("data-naja-history-cache");c.snippetCache=t}}buildHistoryState(t){const{state:e,options:n}=t.detail;"historyUiCache"in n&&(console.warn("Naja: options.historyUiCache is deprecated, use options.snippetCache instead."),n.snippetCache=n.historyUiCache);const i=Q.findSnippets((t=>!(t.hasAttribute("data-naja-history-nocache")||t.hasAttribute("data-history-nocache")||t.hasAttribute("data-naja-snippet-cache")&&"off"===t.getAttribute("data-naja-snippet-cache"))));if(!this.dispatchEvent(new CustomEvent("store",{cancelable:!0,detail:{snippets:i,state:e,options:n}})))return;const r=this.resolveStorage(n.snippetCache);e.snippets={storage:r.type,key:r.store(i)}}restoreHistoryState(t){const{state:e,options:n}=t.detail;if(void 0===e.snippets)return;if(n.snippetCache=e.snippets.storage,!this.dispatchEvent(new CustomEvent("fetch",{cancelable:!0,detail:{state:e,options:n}})))return;const i=this.resolveStorage(n.snippetCache).fetch(e.snippets.key,e,n);null!==i&&this.dispatchEvent(new CustomEvent("restore",{cancelable:!0,detail:{snippets:i,state:e,options:n}}))&&(this.naja.snippetHandler.updateSnippets(i,!0,n),this.naja.scriptLoader.loadScripts(i))}}class tt{constructor(t){this.naja=t,this.type="off"}store(){return null}fetch(t,e,n){return this.naja.makeRequest("GET",e.href,null,Object.assign(Object.assign({},n),{history:!1,snippetCache:!1})),null}}class et{constructor(){this.type="history"}store(t){return t}fetch(t){return t}}class nt{constructor(){this.type="session"}store(t){const e=Math.random().toString(36).substr(2,6);return window.sessionStorage.setItem(e,JSON.stringify(t)),e}fetch(t){const e=window.sessionStorage.getItem(t);return null===e?null:JSON.parse(e)}}class it{constructor(t){this.loadedScripts=new Set,t.addEventListener("init",(()=>{$((()=>{document.querySelectorAll("script[data-naja-script-id]").forEach((t=>{const e=t.getAttribute("data-naja-script-id");null!==e&&""!==e&&this.loadedScripts.add(e)}))})),t.addEventListener("success",(t=>{const{payload:e}=t.detail;e.snippets&&this.loadScripts(e.snippets)}))}))}loadScripts(t){Object.keys(t).forEach((e=>{const n=t[e];if(!/<script/i.test(n))return;const i=window.document.createElement("div");i.innerHTML=n;const r=i.querySelectorAll("script");for(let t=0;t<r.length;t++){const e=r.item(t),n=e.getAttribute("data-naja-script-id");if(null!==n&&""!==n&&this.loadedScripts.has(n))continue;const i=window.document.createElement("script");if(i.innerHTML=e.innerHTML,e.hasAttributes()){const t=e.attributes;for(let e=0;e<t.length;e++){const n=t[e].name;i.setAttribute(n,t[e].value)}}window.document.head.appendChild(i).parentNode.removeChild(i),null!==n&&""!==n&&this.loadedScripts.add(n)}}))}}class rt extends EventTarget{constructor(t,e,n,i,r,o,a){super(),this.VERSION=2,this.initialized=!1,this.extensions=[],this.defaultOptions={},this.uiHandler=new(null!=t?t:Y)(this),this.redirectHandler=new(null!=e?e:X)(this),this.snippetHandler=new(null!=n?n:Q)(this),this.formsHandler=new(null!=i?i:K)(this),this.historyHandler=new(null!=r?r:J)(this),this.snippetCache=new(null!=o?o:Z)(this),this.scriptLoader=new(null!=a?a:it)(this)}registerExtension(t){this.initialized&&t.initialize(this),this.extensions.push(t)}initialize(t={}){if(this.initialized)throw new Error("Cannot initialize Naja, it is already initialized.");this.defaultOptions=this.prepareOptions(t),this.extensions.forEach((t=>t.initialize(this))),this.dispatchEvent(new CustomEvent("init",{detail:{defaultOptions:this.defaultOptions}})),this.initialized=!0}prepareOptions(t){return Object.assign(Object.assign(Object.assign({},this.defaultOptions),t),{fetch:Object.assign(Object.assign({},this.defaultOptions.fetch),null==t?void 0:t.fetch)})}async makeRequest(t,e,n=null,i={}){"string"==typeof e&&(e=new URL(e,location.href)),i=this.prepareOptions(i);const r=new Headers(i.fetch.headers||{}),o=this.transformData(e,t,n),a=new AbortController,s=new Request(e.toString(),Object.assign(Object.assign({credentials:"same-origin"},i.fetch),{method:t,headers:r,body:o,signal:a.signal}));if(s.headers.set("X-Requested-With","XMLHttpRequest"),s.headers.set("Accept","application/json"),!this.dispatchEvent(new CustomEvent("before",{cancelable:!0,detail:{request:s,method:t,url:e.toString(),data:n,options:i}})))return{};const l=window.fetch(s);let c,u;this.dispatchEvent(new CustomEvent("start",{detail:{request:s,promise:l,abortController:a,options:i}}));try{if(c=await l,!c.ok)throw new ot(c);u=await c.json()}catch(t){if("AbortError"===t.name)return this.dispatchEvent(new CustomEvent("abort",{detail:{request:s,error:t,options:i}})),this.dispatchEvent(new CustomEvent("complete",{detail:{request:s,response:c,payload:void 0,error:t,options:i}})),{};throw this.dispatchEvent(new CustomEvent("error",{detail:{request:s,response:c,error:t,options:i}})),this.dispatchEvent(new CustomEvent("complete",{detail:{request:s,response:c,payload:void 0,error:t,options:i}})),t}return this.dispatchEvent(new CustomEvent("success",{detail:{request:s,response:c,payload:u,options:i}})),this.dispatchEvent(new CustomEvent("complete",{detail:{request:s,response:c,payload:u,error:void 0,options:i}})),u}appendToQueryString(t,e,n){if(null!=n)if(Array.isArray(n)||Object.getPrototypeOf(n)===Object.prototype)for(const[i,r]of Object.entries(n))this.appendToQueryString(t,`${e}[${i}]`,r);else t.append(e,String(n))}transformData(t,e,n){const i=["GET","HEAD"].includes(e.toUpperCase());if(i&&n instanceof FormData){for(const[e,i]of n)null!=i&&t.searchParams.append(e,String(i));return null}if(null!==n&&Object.getPrototypeOf(n)===Object.prototype||Array.isArray(n)){const e=i?t.searchParams:new URLSearchParams;for(const[t,i]of Object.entries(n))this.appendToQueryString(e,t,i);return i?null:e}return n}}class ot extends Error{constructor(t){const e=`HTTP ${t.status}: ${t.statusText}`;super(e),this.name=this.constructor.name,this.stack=new Error(e).stack,this.response=t}}const at=new rt;return at.registerExtension(new class{constructor(){this.abortable=!0,this.abortController=null}initialize(t){t.uiHandler.addEventListener("interaction",this.checkAbortable.bind(this)),t.addEventListener("init",this.onInitialize.bind(this)),t.addEventListener("before",this.checkAbortable.bind(this)),t.addEventListener("start",this.saveAbortController.bind(this)),t.addEventListener("complete",this.clearAbortController.bind(this))}onInitialize(){document.addEventListener("keydown",(t=>{null!==this.abortController&&"Escape"===t.key&&!(t.ctrlKey||t.shiftKey||t.altKey||t.metaKey)&&this.abortable&&(this.abortController.abort(),this.abortController=null)}))}checkAbortable(t){var e,n;const{options:i}=t.detail;this.abortable="element"in t.detail?"off"!==(null!==(e=t.detail.element.getAttribute("data-naja-abort"))&&void 0!==e?e:null===(n=t.detail.element.form)||void 0===n?void 0:n.getAttribute("data-naja-abort")):!1!==i.abort,i.abort=this.abortable}saveAbortController(t){const{abortController:e}=t.detail;this.abortController=e}clearAbortController(){this.abortController=null,this.abortable=!0}}),at.registerExtension(new class{constructor(){this.abortControllers=new Map}initialize(t){t.uiHandler.addEventListener("interaction",this.checkUniqueness.bind(this)),t.addEventListener("start",this.abortPreviousRequest.bind(this)),t.addEventListener("complete",this.clearRequest.bind(this))}checkUniqueness(t){var e,n;const{element:i,options:r}=t.detail,o=null!==(e=i.getAttribute("data-naja-unique"))&&void 0!==e?e:null===(n=i.form)||void 0===n?void 0:n.getAttribute("data-naja-unique");r.unique="off"!==o&&(null!=o?o:"default")}abortPreviousRequest(t){var e,n,i;const{abortController:r,options:o}=t.detail;!1!==o.unique&&(null===(n=this.abortControllers.get(null!==(e=o.unique)&&void 0!==e?e:"default"))||void 0===n||n.abort(),this.abortControllers.set(null!==(i=o.unique)&&void 0!==i?i:"default",r))}clearRequest(t){var e;const{request:n,options:i}=t.detail;n.signal.aborted||!1===i.unique||this.abortControllers.delete(null!==(e=i.unique)&&void 0!==e?e:"default")}}),at.Naja=rt,at.HttpError=ot,at}));
//# sourceMappingURL=Naja.min.js.map
