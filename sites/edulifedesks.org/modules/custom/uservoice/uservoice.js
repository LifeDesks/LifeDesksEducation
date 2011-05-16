$(document).ready(function() {
  $('.uservoice-feedback').each(function() {
    $(this).click(function() {
      UserVoice.Popin.show(uservoiceOptions);
      return false;
    });
  });
});