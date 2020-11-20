bin_PROGRAMS=guess_number
pkgdata_DATA=ru/LC_MESSAGES/guess_number.mo

@DX_RULES@

ru/LC_MESSAGES/guess_number.mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

ru.po:	messages.pot
	msgmerge -U $@ $<

messages.pot:	guess_number.pot guess_number.c
	xgettext -k_ -c guess_number.c -o messages.new.pot
	cp guess_number.pot messages.pot
	msgmerge -U messages.pot messages.new.pot

clean:
	rm -rf ru
	rm messages.new.pot
	rm guess_number
