(function(d){var c=location.href.replace(/#.*/,""),b=d.localScroll=function(e){d("body").localScroll(e)};b.defaults={duration:1000,axis:"y",event:"click",stop:1};b.hash=function(e){e=d.extend({},b.defaults,e);e.hash=0;if(location.hash){setTimeout(function(){a(0,location,e)},0)}};d.fn.localScroll=function(e){e=d.extend({},b.defaults,e);return(e.persistent||e.lazy)?this.bind(e.event,function(h){var g=d([h.target,h.target.parentNode]).filter(f)[0];g&&a(h,g,e)}):this.find("a,area").filter(f).bind(e.event,function(g){a(g,this,e)}).end().end();function f(){var g=this;return !!g.href&&!!g.hash&&g.href.replace(g.hash,"")==c&&(!e.filter||d(g).is(e.filter))}};function a(j,h,g){var l=h.hash.slice(1),k=document.getElementById(l)||document.getElementsByName(l)[0],i;if(k){j&&j.preventDefault();i=d(g.target||d.scrollTo.window());if(g.lock&&i.is(":animated")||g.onBefore&&g.onBefore.call(h,j,k,i)===!1){return}if(g.stop){i.queue("fx",[]).stop()}i.scrollTo(k,g).trigger("notify.serialScroll",[k]);if(g.hash){i.queue(function(){location=h.hash;d(this).dequeue()})}}}})(jQuery);