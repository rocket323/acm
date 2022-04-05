#include <stdio.h>
#include <sstream>

char tmp[100], ch;
int m, y, d, hor, min, sec;

int main()
{
	int t;
	scanf("%d\n", &t);
	while(t--)
	{
		gets(tmp);
		sscanf(tmp, "%d%c%d%c%d%c%d%c%d%c%d", &y, &ch, &m, &ch, &d, &ch, &hor, &ch, &min, &ch, &sec);

		printf("%02d/%02d/%d-", m, d, y);
		if(hor >= 12) printf("%02d:%02d:%02dpm\n", hor > 12 ? hor - 12 : 12, min, sec);
		else printf("%02d:%02d:%02dam\n", hor == 0 ? 12 : hor, min, sec);
	}
	return 0;
}

