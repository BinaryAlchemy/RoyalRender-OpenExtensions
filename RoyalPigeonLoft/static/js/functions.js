function ajax_jobs_table(group, groupId, targetElement) {

  $('#' + targetElement).colResizable({disable: true});
  var xhttp = new XMLHttpRequest();
  var targetElementHead = targetElement + 'head';
  var targetElementBody = targetElement + 'body';

  removeSelectRows(targetElement);

  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      hideLoadingSpinner();
      var jsonResponse = JSON.parse(this.responseText);
      document.getElementById(targetElementHead).innerHTML = jsonResponse['htmlHead'];
      document.getElementById(targetElementBody).innerHTML = jsonResponse['htmlBody'];

      applySelectRows(targetElement);

      $('#' + targetElement).colResizable({
        disable:false,
        postbackSafe:true,
        partialRefresh:true,
        liveDrag:true,
        draggingClass:'dragging',
        resizeMode:'overflow'});

      var time_now = getSimpleTime();
      document.getElementById(groupId + 'lastUpdate').innerHTML = time_now;

    } else if (this.status == 403) {
      window.location.href = "login";
    }
  };

  showLoadingSpinner();
  xhttp.open("POST", "/project", true);
  xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
  xhttp.send("project="+ group + "&id=" + groupId);
}

function ajax_clients_table(group, groupId, targetElement) {

  $('#' + targetElement).colResizable({disable: true});
  var xhttp = new XMLHttpRequest();
  var targetElementHead = targetElement + 'head';
  var targetElementBody = targetElement + 'body';

  removeSelectRows(targetElement);

  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      hideLoadingSpinner();
      var jsonResponse = JSON.parse(this.responseText);
      document.getElementById(targetElementHead).innerHTML = jsonResponse['htmlHead'];
      document.getElementById(targetElementBody).innerHTML = jsonResponse['htmlBody'];

      applySelectRows(targetElement);

      $('#' + targetElement).colResizable({
        disable:false,
        postbackSafe:true,
        partialRefresh:true,
        liveDrag:true,
        draggingClass:'dragging',
        resizeMode:'overflow'});

      var time_now = getSimpleTime();
      document.getElementById(groupId + 'lastUpdate').innerHTML = time_now;

    } else if (this.status == 403) {
      window.location.href = "login";
    }
  };

  showLoadingSpinner();
  xhttp.open("POST", "/client_group", true);
  xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
  xhttp.send("group="+ group + "&id=" + groupId);
}

function execute_command_on_selected_jobs(command) {

  var selected_jobs_rows = $("tr.selected-row");

  if (selected_jobs_rows.length == 0) {
    alert("Select some job first");
    return;
  }

  if (!confirm('Execute command: "' + command + '" on Selected jobs?')) {return}

  var id_list = [];

  for (var i = 0; i < selected_jobs_rows.length; i++) {
    id_list.push( $(selected_jobs_rows[i]).attr("data-job_id") );
  }

  var xhttp = new XMLHttpRequest();

  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var jsonResponse = JSON.parse(this.responseText);
      if ( jsonResponse['out'] == 'fail' ) {
        var message = ('content' in jsonResponse)? jsonResponse['content']: '';
        hideLoadingSpinner();
        alert("Could not execute command: " + message);
      } else {
        hideLoadingSpinner();
        alert("Command succesfully executed");
        updateOpenGroups();
      }
    } else if (this.status == 403) {
      window.location.href = "login";
    }

  };

  showLoadingSpinner();
  xhttp.open("POST", "/job_command", true);
  xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
  xhttp.send("jobs_list="+ id_list + "&command=" + command);

}

function execute_command_on_selected_clients(command) {


  var selected_clients_rows = $("tr.selected-row");

  if (selected_clients_rows.length == 0) {
    alert("Select some client first");
    return;
  }

  if (!confirm('Execute command: ' + command + " on Selected clients?")) {return}

  var id_list = [];

  for (var i = 0; i < selected_clients_rows.length; i++) {
    id_list.push( $(selected_clients_rows[i]).attr("data-client_id") );
  }

  var xhttp = new XMLHttpRequest();

  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var jsonResponse = JSON.parse(this.responseText);
      if ( jsonResponse['out'] == 'fail' ) {
        var message = ('content' in jsonResponse)? jsonResponse['content']: '';
        hideLoadingSpinner();
        alert("Could not execute command: " + message);
      } else {
        hideLoadingSpinner();
        alert("Command succesfully executed");
      }
    } else if (this.status == 403) {
      window.location.href = "login";
    }
  };

  showLoadingSpinner();
  xhttp.open("POST", "/client_command", true);
  xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
  xhttp.send("clients_list="+ id_list + "&command=" + command);

}

function showLoadingSpinner() {
  $('#loadingSpinner').modal('show');
}

function hideLoadingSpinner() {
  $("#loadingSpinner").modal('hide');
}

function getSimpleTime() {
  var d = new Date();
  var hr = d.getHours();
  var min = d.getMinutes();
  if (hr < 10) {
    hr = "0" + hr;
  }
  if (min < 10) {
    min = "0" + min;
  }

  var time_now = hr + ":" + min;
  return time_now;
}

function showJobDetails() {
  var rows = $(".selected-row");
  if (rows.length == 0) {return}

  var row_ids = [];
  $.each(rows, function(index, item) {
    row_ids.push($(item).attr("data-job_id"));
  });
  location.assign("/jobs_detail?job_id=" + row_ids );
}

function showClientDetails() {
  var rows = $(".selected-row");
  if (rows.length == 0) {return}

  var row_ids = [];
  $.each(rows, function(index, item) {
    row_ids.push($(item).attr("data-client_id"));
  });
  location.assign("/clients_detail?client_id=" + row_ids );
}

function updateOpenGroups() {
  var openCollapse = $(".collapse.show");
  $.each(openCollapse, function(index, item) {

    var cardHeader = $(item).siblings(".card-header");
    var btn = $(cardHeader).find(".refreshable");
    btn.click();
  });
}

function watchForHover() {
    var hasHoverClass = true;
    var lastTouchTime = 0;

    function enableHover() {
        // filter emulated events coming from touch events
        var container = $(document.body);
        if (new Date() - lastTouchTime < 500) return;
        if (hasHoverClass) return;

        container.addClass('hasHover');
        hasHoverClass = true;
    }

    function disableHover() {
        var container = $(document.body);
        if (!hasHoverClass) return;

        container.removeClass('hasHover');
        hasHoverClass = false;
    }

    function updateLastTouchTime() {
        lastTouchTime = new Date();
    }

    document.addEventListener('touchstart', updateLastTouchTime, true);
    document.addEventListener('touchstart', disableHover, true);
    document.addEventListener('mousemove', enableHover, true);

}

function hideMessagesTimer() {
  $(document).ready(function () {
    setTimeout(function () {
        $('div.messageClass').animate({"opacity": 0});
    }, 2000);
  });
}

function disableTextSelection() {
	document.onselectstart = function () {
		return false;
	}
}

function enableTextSelection() {
	document.onselectstart = function () {
		return true;
	}
}

function disableShiftSelect () {
	$(document.body).keydown(
		function (event) {
			if (event.shiftKey) {
				disableTextSelection();
			}
		}
	);
	$(document.body).on("keyup",
		function (event) {
			if (event.originalEvent.key === "Shift") {
				enableTextSelection();
			}
		}

	);
}

watchForHover();
hideMessagesTimer();
disableShiftSelect();