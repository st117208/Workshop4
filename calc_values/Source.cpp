#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

void in(float** a, float k, float n)
{
	std::ifstream in("Input.csv");
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			in >> a[i][j];
		}
	}
}

void tx(float** a, float k, float n, float t_x[])
{
	for (int i = 0; i < k; ++i)
	{
		float sum = 0;
		for (int j = 0; j < n; ++j)
		{
			sum = sum + a[j][i];
		}
		t_x[i] = sum / n;
	}
}

void gi(float k, float n, float t_x[], float g[])
{
	float h = 0.272;
	float v0 = 1.050;
	for (int i = 0; i < k; ++i)
	{
		g[i] = 2 * (h - (v0 * t_x[i] / 1000)) / pow(t_x[i] / 1000, 2);
	}
}

void dt(float** a, float k, float n, float t_x[], float t_err[])
{
	for (int i = 0; i < k; ++i)
	{
		float sum = 0.0;
		for (int j = 0; j < n; ++j)
		{
			sum = sum + pow(a[j][i] - t_x[i], 2);
		}
		t_err[i] = sqrt(sum / (n * (n - 1)));
	}
}

void dg(float k, float t_x[], float t_err[], float g_err[], float V0, float dV0, float h, float dh)
{
	for (int i = 0; i < k; ++i)
	{
		float tmp = t_x[i] / 1000;
		float ch = 4 / (9 * std::pow(tmp, 4));
		float cV0 = 4 / (9 * std::pow(tmp, 2));
		float ct = ((2 * V0 * tmp - 4 * h) / pow(tmp, 3)) * ((2 * V0 * tmp - 4 * h) / pow(tmp, 3));
		g_err[i] = sqrt(ch * pow(dh, 2) + cV0 * pow(dV0, 2) + pow(t_err[i], 2) * ct / 1000000);
	}
}


void out(float** a, float k, float n, float t_x[], float t_err[], float g[], float g_err[], float V0, float dV0, float h, float dh)
{
	std::ofstream out("Output.csv");

	tx(a, k, n, t_x);
	gi(k, n, t_x, g);
	dt(a, k, n, t_x, t_err);
	dg(k, t_x, t_err, g_err, V0, dV0, h, dh);

	for (int i = 0; i < k; ++i)
	{
		out << std::setprecision(6) << t_x[i] << "  " << std::setprecision(6) << t_err[i] << "  "
			<< std::setprecision(3) << g[i] << "  " << std::setprecision(1) << g_err[i] << "  " << std::endl;
	}
}

int main()
{
	float c = 6;
	float n = 30;
	float** a = new float* [c];
	for (int i = 0; i < n; ++i)
	{
		a[i] = new float[n];
	}

	float V0 = 1.05;
	float dV0 = 0.005;
	float h = 0.272;
	float dh = 0.0001;

	float average[6];
	float terror[6];
	float g[6];
	float gerror[6];

	in(a, c, n);
	out(a, c, n, average, terror, g, gerror, V0, dV0, h, dh);

	return EXIT_SUCCESS;
}