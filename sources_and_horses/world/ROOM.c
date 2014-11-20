void makeMaze(PROG *pM, INPUT *pI, FILE *file)
{
	pM -> maze = 0;

	pM -> maze = (char **)calloc((pI -> length) + 1, sizeof(char *));
	if (pM -> maze == NULL)
	{
		fprintf(stderr, "No memory available.\n");
		exit(3);
	}

	for(int i = 0; i < pI -> length + 1; i++)
	{
		pM -> maze[i] = (char *)calloc((pI -> width) + 1, sizeof(char));
		if (pM -> maze[i] ==  NULL)
		{
			fprintf(stderr, "No memory available.\n");
			exit(4);
		}
	}

	fseek(file, pI -> arrayinfile - (pI -> width + 1), SEEK_SET);

	for (int i = 0; i <= pI -> length; i++)
	{
		for (int j = 0; j <= pI -> width; j++)
		{
			pM -> maze[i][j] = fgetc(file);
		}
	}
}