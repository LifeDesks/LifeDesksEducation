$(document).ready(function() {
  // open external links in new window
  $('a[@href^=http]').not('[@href*=edulifedesks.org], [@href*=uservoice.com], [@href*=creativecommons.org]').addClass('external-link').click(function() {
    window.open(this.href, '_blank');
    return false;
  });
  // change styles on hover of form submit buttons
  $('.form-submit').each(function() {
    $(this).mouseover(function() {
      $(this).addClass('on');
    });
    $(this).mouseout(function() {
      $(this).removeClass('on');
    });
  });
  // change style of fake file field browse button when event occurs on real button
  $('.form-file').each(function() {
    $(this).mouseover(function() {
      $(this).prev().children('.pseudo-file-text').addClass('on');
      $(this).prev().children('.pseudo-file-button').addClass('on');
    });
    $(this).mouseout(function() {
      $(this).prev().children('.pseudo-file-text').removeClass('on');
      $(this).prev().children('.pseudo-file-button').removeClass('on');
    });
  });
  // change style of fieldset legend on hover
  $('.optional-fields fieldset legend a').each(function() {
    $(this).mouseover(function() {
      $(this).parent().parent().addClass('on');
    });
    $(this).mouseout(function() {
      $(this).parent().parent().removeClass('on');
    });
  });
});
