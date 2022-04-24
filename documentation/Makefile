BUILD_DIR=build

REPORT_DIR=report
REPORT_BUILD_DIR=$(REPORT_DIR)/$(BUILD_DIR)

.PHONY: all
all: report

report: $(REPORT_BUILD_DIR)/report.pdf

$(REPORT_BUILD_DIR)/report.pdf: $(REPORT_DIR)/report.tex $(REPORT_DIR)/references.bib
	mkdir -p $(REPORT_BUILD_DIR)
	cd $(REPORT_DIR) && latexmk -outdir=$(BUILD_DIR) -pdf

.PHONY: clean
clean:
	rm $(REPORT_BUILD_DIR)/*
