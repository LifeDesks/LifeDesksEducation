var CLASSCHKR = {};

CLASSCHKR.checkName = function() {
  var _this = this;
  var message = '';
  var sciname = $('#edit-field-dwc-scientificname-0-value').val();
  sciname = sciname.replace(/(<([^>]+)>)/ig,""); 

  if(sciname != Drupal.t('Scientific name') && sciname != "") {

	//show the spinner
	message = '<div class="messages status classification-checker throbber">' + Drupal.t('Looking for %sciname ...', {'%sciname' : sciname}) + '</div>';
	_this.showMessage(message);
	
    $.post(Drupal.settings.basePath + "classification_checker/lookup", {"search" : sciname}, function(data) {
	    if(data.status == "ok") {
		  if(!data.data) {
			message = '<div class="messages error classification-checker">' + data.message;
	        message += '<p><input type="submit" id="classification-checker-ok" class="form-submit button-submit" value="' + Drupal.t('OK') + '"></p>';
	        message += '</div>';
			_this.showMessage(message);
			$('#classification-checker-ok').click(function() { _this.hideMessage(); return false; });
		    return;	
		  }

		  message = '<div class="messages status classification-checker">' + data.message;

          var ranks = [];

		  if(data.data.length > 1) {
		    message += '<ul>'
		    for(var i=0;i<data.data.length;i++) {
			  message += '<li><input type="radio" name="classification-checker-selection" value="' + i + '">' + data.data[i].ranked_ancestry + ' (' + Drupal.t('See the !name page on EOL', {'!name' : '<a href="http://www.eol.org/' + data.data[i].last_ranked_name + '" target="_blank">' + data.data[i].last_ranked_name + '</a>'}) + ')</li>';
			  ranks[i] = data.data[i].ranks;
		    }
		    message += '</ul>';	
		  }
		  else {
		    message += '<p>' + data.data[0].ranked_ancestry + ' (' + Drupal.t('See the !name page on EOL', {'!name' : '<a href="http://www.eol.org/' + encodeURI(data.data[0].canonical) + '" target="_blank">' + data.data[0].canonical + '</a>'}) + ')</p>';
		    ranks[0] = data.data[0].ranks;
		  }
	      message += '<input type="submit" id="classification-checker-ok" class="form-submit button-submit" value="' + Drupal.t('Copy Names') + '">';
	      message += '<input type="submit" id="classification-checker-cancel" class="form-submit button-cancel" value="' + Drupal.t('Cancel') + '">';
	      message += '</p>';
	      message += '</div>';
	
		  _this.showMessage(message);
		
		  $('#classification-checker-ok').click(function() {
			if($("input[name='classification-checker-selection']").length > 0 && typeof($("input[name='classification-checker-selection']:checked").val()) != 'undefined') {
			  _this.applyRanks(ranks[$("input[name='classification-checker-selection']:checked").val()]);
			  $('#edit-field-dwc-scientificname-0-value').addClass('classification-checker-copied').val(data.data[0].found_name);	
			}
			else if ($("input[name='classification-checker-selection']").length == 0) {
			  _this.applyRanks(ranks[0]);
			  $('#edit-field-dwc-scientificname-0-value').addClass('classification-checker-copied').val(data.data[0].found_name);
			}
			else {}
			return false; 
		  });
		  $('#classification-checker-cancel').click(function() { _this.hideMessage(); return false; });
		}
		else {
			message = '<div class="messages error classification-checker">' + data.message;
	        message += '<p><input type="submit" id="classification-checker-ok" class="form-submit button-submit" value="' + Drupal.t('OK') + '"></p>';
	        message += '</div>';
			_this.showMessage(message);
			$('#classification-checker-ok').click(function() { _this.hideMessage(); return false; });
		} 
    }, 'json');
  }	
}

CLASSCHKR.showMessage = function(message) {
  $('body').append('<div id="classification-checker-overlay"></div><div id="classification-checker-message"></div>');
  var arrPageSizes = ___checkerGetPageSize();
  $('#classification-checker-overlay').css({
	backgroundColor: 'black',
	opacity: 0.66,
	width: arrPageSizes[0],
	height: arrPageSizes[1]
  });
  var arrPageScroll = ___checkerGetPageScroll();
  $('#classification-checker-message').css({
	top: 150,
	left: arrPageScroll[0],
	position: 'fixed',
	zIndex: 1001,
	margin: '0px auto',
	width: '100%'
  });
  $('#classification-checker-overlay').show();
  $('#classification-checker-message').html(message).show();	
}

CLASSCHKR.hideMessage = function() {
  $('#classification-checker-message').hide();
  $('#classification-checker-overlay').hide();
}

CLASSCHKR.applyRanks = function(ranks) {

  //remove all classes from previous searches & clear out input boxes
  $('#edit-field-dwc-scientificname-0-value').removeClass('classification-checker-copied');
  $(".group-classification").find("input").each(function() { $(this).removeClass('classification-checker-copied').val(''); });

    // extend jQuery to get the keys in a JSON object
	$.extend({
	    keys:    function(obj){
	        var a = [];
	        $.each(obj, function(k){ a.push(k) });
	        return a;
	    }
	});
	
	var rank_keys = $.keys(ranks);
	var fields_ids = Drupal.settings.classification_checker_fieldranks;
	
	for(var i=0; i<=rank_keys.length; i++) {
		$('#' + fields_ids[rank_keys[i]]).addClass("classification-checker-copied").val(ranks[rank_keys[i]]);
	}
	
	//expand the collapsed classification fieldset
	var $fieldset = $(".group-classification");
	if($fieldset.hasClass("collapsed")) {
	  Drupal.toggleFieldset('.group-classification');
    }
    
    this.hideMessage();

    $('.classification-checker-copied').each(function() {
	  $(this).keyup(function() {
        $('.classification-checker-copied').removeClass('classification-checker-copied');
      });
    });

    $('#edit-field-dwc-scientificname-0-value').keyup(function() {
	  $('.classification-checker-copied').removeClass('classification-checker-copied');
    });

	return;
}

function ___checkerGetPageSize() {
	var xScroll, yScroll;
	if (window.innerHeight && window.scrollMaxY) {	
		xScroll = window.innerWidth + window.scrollMaxX;
		yScroll = window.innerHeight + window.scrollMaxY;
	} else if (document.body.scrollHeight > document.body.offsetHeight){ // all but Explorer Mac
		xScroll = document.body.scrollWidth;
		yScroll = document.body.scrollHeight;
	} else { // Explorer Mac...would also work in Explorer 6 Strict, Mozilla and Safari
		xScroll = document.body.offsetWidth;
		yScroll = document.body.offsetHeight;
	}
	var windowWidth, windowHeight;
	if (self.innerHeight) {	// all except Explorer
		if(document.documentElement.clientWidth){
			windowWidth = document.documentElement.clientWidth; 
		} else {
			windowWidth = self.innerWidth;
		}
		windowHeight = self.innerHeight;
	} else if (document.documentElement && document.documentElement.clientHeight) { // Explorer 6 Strict Mode
		windowWidth = document.documentElement.clientWidth;
		windowHeight = document.documentElement.clientHeight;
	} else if (document.body) { // other Explorers
		windowWidth = document.body.clientWidth;
		windowHeight = document.body.clientHeight;
	}
	// for small pages with total height less then height of the viewport
	if(yScroll < windowHeight){
		pageHeight = windowHeight;
	} else { 
		pageHeight = yScroll;
	}
	// for small pages with total width less then width of the viewport
	if(xScroll < windowWidth){	
		pageWidth = xScroll;		
	} else {
		pageWidth = windowWidth;
	}
	arrayPageSize = new Array(pageWidth,pageHeight,windowWidth,windowHeight);
	return arrayPageSize;
}

function ___checkerGetPageScroll() {
	var xScroll, yScroll;
	if (self.pageYOffset) {
		yScroll = self.pageYOffset;
		xScroll = self.pageXOffset;
	} else if (document.documentElement && document.documentElement.scrollTop) {	 // Explorer 6 Strict
		yScroll = document.documentElement.scrollTop;
		xScroll = document.documentElement.scrollLeft;
	} else if (document.body) {// all other Explorers
		yScroll = document.body.scrollTop;
		xScroll = document.body.scrollLeft;	
	}
	arrayPageScroll = new Array(xScroll,yScroll);
	return arrayPageScroll;
}

$(function() {
    $('.classification-checker-copied').each(function() {
	  $(this).keyup(function() {
        $('.classification-checker-copied').removeClass('classification-checker-copied');
      });
    });

    $('#edit-field-dwc-scientificname-0-value').keyup(function() {
	  $('.classification-checker-copied').removeClass('classification-checker-copied');
    });	
});

$(window).resize(function() {
	// Get page sizes
	var arrPageSizes = ___checkerGetPageSize();
	// Style overlay and show it
	$('#classification-checker-overlay').css({
		width: arrPageSizes[0],
		height: arrPageSizes[1]
	});
	var arrPageScroll = ___checkerGetPageScroll();
	$('#classification-checker-message').css({
		top: arrPageScroll[1] + (arrPageSizes[3] / 3.5),
		left: arrPageScroll[0],
		position: 'fixed',
		zIndex: 1001,
		margin: '0px auto',
		width: '100%'
	});
});