// Uncomment the following function if you want to disable text selection
/*document.onselectstart = function() {
	// disables text selection
	return false;
};*/

function isHover() {

	var container = $(document.body);
	return container.hasClass('hasHover');

}

function toggleRow(table, row) {

  if ($(row).hasClass('selected-row')) {
    $(row).removeClass('selected-row');
    $(table).attr("data-active_row", "");
  } else {
    $(row).addClass('selected-row');
    $(table).attr("data-active_row", row.rowIndex);
  }
}

function selectRowsBetweenIndexes(table, indexes) {
	var trs = $(table).find('> tbody > tr');
    indexes.sort(function(a, b) {
        return a - b;
    });

    for (var i = indexes[0]; i <= indexes[1]; i++) {
    	var row = $(trs[i-1]);
		if (!row.hasClass('selected-row')) {
			row.addClass('selected-row');
			$(table).attr("data-active_row", row[0].rowIndex);
		}
    }
}

function clearAll(table) {
	var trs = $(table).find('> tbody > tr.selected-row');
	for (var i = 0; i < trs.length; i++) {
		$(trs[i]).removeClass('selected-row');
	}
	$(table).attr("data-active_row", "");
}

function selectAll(table) {
  	var trs = $(table).find('> tbody > tr:not(.selected-row)');
	for (var i = 0; i < trs.length; i++) {
		$(trs[i]).addClass('selected-row');
	}
	$(table).attr("data-active_row", "1");
}

function removeSelectRows(table) {
	// removes event listeners
	$('#' + table).off('mousedown');
	$('#' + table + ' tbody tr').off('click');
}

function applySelectRows(table) {
	// applies event listeners

	var table_obj = $('#' + table);

	table_obj.on('mousedown', function(e) {
		// this removes annoying td border highlight on click
    if (e.ctrlKey) {
        e.preventDefault();
    }
	});

	$('#' + table + ' tbody tr').click(function(event) {

		if (!isHover()) {
			toggleRow(table_obj, this);
			return;
		}

		if ( event.ctrlKey ) {
			toggleRow(table_obj, this);
		}  else if ( event.shiftKey ){
			var currentIndex = $(table_obj).attr("data-active_row");
			if (  currentIndex === "" ) {
				currentIndex = this.rowIndex;
			}
			selectRowsBetweenIndexes(table_obj, [this.rowIndex, currentIndex]);
		} else {

			var toggle = true;
			if ($( this ).hasClass('selected-row')) {
				toggle = false;
			}
			clearAll(table_obj);
			if (toggle) {
				toggleRow(table_obj, this);
			}
		}

	});

}