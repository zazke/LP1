void readRecordsWriteReport();
void writeHeader(char *esp1, char *esp2, int curDate);
void readWriteMedicos(
        int curDate,
        char *esp1, int &med1Qty, int &pac1Qty, int &medVencida1Qty,
        char *esp2, int &med2Qty, int &pac2Qty, int &medVencida2Qty
);
void readWritePacientes(
        int curDate,
        char *esp,
        char *esp1, int &pac1Qty, int &medVen1Qty,
        char *esp2, int &pac2Qty, int &medVen2Qty
);
void readWriteMedicinas(int n,
        int &medVenCnt,
        int curDate,
        char *esp,
        char *esp1, int &medVen1Qty,
        char *esp2, int &medVen2Qty
);
void writeformattedMedico(char *id, char *name, char *esp);
void writeformattedPaciente(int i, int dni, char *name);
void writeformattedMedicina(int i, int id, char *name, int venDate, int qty,
        int curDate
);

void writeformattedResumen(
        char *esp1, int med1Qty, int pac1Qty, int medVencida1Qty,
        char *esp2, int med2Qty, int pac2Qty, int medVencida2Qty
);
void writeformattedResumenLine(
        char *esp, int medQty, int pacQty, int medVencidaQty
);

void separateNameEsp(char *name, char *esp);
