#ifndef _RAMON_DATE_H_
#define _RAMON_DATE_H_

#include <time.h>
#include <string>
#include <cstdint>

// busca a plataforma do cliente
#if (defined _WIN32) || (defined WIN32) || (defined _WIN64) || (defined WIN64)
#define PLATFORM_WINDOWS
#endif

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#else
#include <sys/time.h>
#endif

typedef int64_t int64;

namespace ec
{

class Time;
class Date;
class Duration;


/**
 * @brief Classe que representa um intervalo de tempo.
 */
class Duration
{
public:
	/**
	 * @brief Tipo de tempo, o nível sobe, a precisão cai.
	 */
	enum Period
	{
		/**
		 * @brief Microsegundo 1/1000000 seconds
		 */
		MicroSecond = 5,
		/**
		 * @brief Milisegundos 1/1000 seconds
		 */
		MilliSecond = 6,
		/**
		 * @brief Segundos
		 */
		Second = 11,
		/**
		 * @brief Minutos
		 */
		Minute = 12,
		/**
		 * @brief Horas
		 */
		Hour = 13,
		/**
		 * @brief Dias
		 */
		Day = 14,
		/**
		 * @brief Semanas
		 */
		Week = 15,
		/**
		 * @brief Meses
		 */
		Month = 22,
		/**
		 * @brief Anos
		 */
		Year = 23,
	};

	/**
	 * @brief Construtor de um intervalo de tempo.
	 * 
	 * @param value 
	 * @param period 
	 */
	Duration(int64 value = 1, Period period = Second);

	/**
	 * @brief Construtor de um intervalo de tempo.
	 * 
	 * @param duration 
	 */
	Duration(const Duration &duration);

	/**
	 * @brief Destrói o intervalo de tempo.
	 */
	~Duration();

	/**
	 * @brief Clona o intervalo de tempo.
	 * 
	 * @return Duration 
	 */
	Duration clone() const;

	/**
	 * @brief Retorna o valor do intervalo de tempo.
	 * 
	 * @return int64 
	 */
	inline int64 value() const
	{
		return _value;
	}

	/**
	 * @brief Retorna o tipo do intervalo de tempo.
	 * 
	 * @return Period 
	 */
	inline Period period() const
	{
		return _period;
	}

	/**
	 * @brief Retorna o valor do intervalo de tempo em segundos.
	 * 
	 * @return int64 
	 */
	Duration & set(int64 value, Period period = Second);
	
	/**
	 * @brief Retorna o valor do intervalo de tempo em segundos.
	 * 
	 * @return int64 
	 */
	Duration & setValue(int64 value);
	
	/**
	 * @brief Retorna o tipo do intervalo de tempo.
	 * 
	 * @return Period 
	 */	
	Duration & setPeriod(Period period);

	/**
	 * @brief Promove o nível, reduz a precisão, esta conversão não é precisa, quando a conversão da semana para o mês, a conversão é 1:4.
	 */
	Duration & rase();

	/**
	 * @brief Reduz o nível, aumenta a precisão, esta conversão não é precisa, quando a conversão do mês para a semana, a conversão é 1:4.
	 */
	Duration & down();

	/**
	 * @brief Converte para o tipo especificado.
	 *
	 * @param period
	 * @return Duration
	 */
	Duration & as(Period period);

	/**
	 * @brief Retorna o valor do intervalo de tempo em segundos.
	 * 
	 * @return int64 
	 */
	int64 valueAs(Period period) const;

	// define os operadores
	Duration operator + (const Duration &other);
	Duration operator + (int64 value);
	Duration operator - (const Duration &other);
	Duration operator - (int64 value);
	Duration & operator += (const Duration &other);
	Duration & operator += (int64 value);
	Duration & operator -= (const Duration &other);
	Duration & operator -= (int64 value);
	bool operator > (const Duration & other);
	bool operator >= (const Duration & other);
	bool operator == (const Duration & other);
	bool operator != (const Duration & other);
	bool operator < (const Duration & other);
	bool operator <= (const Duration & other);
private:
	/**
	 * @brief Valor do intervalo de tempo.
	 */
	int64 _value;

	/**
	 * @brief  Tipo do intervalo de tempo.
	 */
	Period _period;
};


/**
 * @brief Classe que representa uma data.
 */
class Date
{
public:
	/**
	 * @brief retorna o timezone local
	 * 
	 * @return int 
	 */
	static int localTimeZone();

	/**
	 * @brief Retorna o timezone local em segundos.
	 * 
	 * @return int 
	 */
	static time_t localTimeZoneOffset();

	/**
	 * @brief Retorna se é um ano bissexto.
	 * 
	 * @param year
	 * @return true
	 * @return false 
	 */
	static bool isLeapYear(int year);

	/**
	 * @brief Retorna o número de dias do mês.
	 * 
	 * @param year
	 * @param month
	 * @return int 
	 */
	static int yearMonthDays(int year, int month);

public:
	/*
	 * @brief Construtor de uma data.
	 */
	Date();

	/**
	 * @brief Construtor de uma data.
	 * 
	 * @param stamp
	 * @param utc
	 */
	Date(time_t stamp, bool utc = false);

	/**
	 * @brief Construtor de uma data.
	 * 
	 * @param time
	 * @param utc
	 */
	Date(const Time &time);

	/**
	 * @brief Construtor de uma data.
	 * 
	 * @param date
	 */
	Date(const Date &other);

	/**
	 * @brief Construtor de uma data.
	 * 
	 * @param year
	 * @param month
	 * @param day
	 * @param hour
	 * @param minute
	 * @param second
	 */
	Date(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);

	~Date();

	/**
	 * @brief Clona a data.
	 * 
	 * @return Date 
	 */
	Date clone() const;
	/**
	 * @brief Converte para UTC.
	 * 
	 * @return Date 
	 */
	Date toUTC() const;

	/**
	 * @brief Converte para Time.
	 * 
	 * @return Time 
	 */
	Time toTime() const;

	/**
	 * @brief Converte para string, o formato é 1970-01-01 00:00:00.
	 * 
	 * @return String 
	 */
	std::string toString() const;

	/**
	 * @brief Formata a string
	 * @param fmt format
	 * @details
	 * %Y ano (e.g. 2004)
	 * %m mês (01-12)
	 * %d dia do mês (01-31)
	 * %H hora (00-23)
	 * %M minuto (00-59)
	 * %S segundo (00-59)
	 * %X string de tempo padrão (e.g. 23:01:59)
	 * %% simbolo de porcentagem
	 * @return se um erro ocorrer, retorna uma string vazia
	 */

	std::string format(const char * fmt = "%Y-%m-%d %H:%M:%S") const;

	/**
	 * @brief Retorna o ano.
	 * 
	 * @return int 
	 */
	inline int year() const
	{
		return _tm.tm_year + 1900;
	}

	/**
	 * @brief Retorna o mês.
	 * 
	 * @return int 
	 */
	inline int month() const
	{
		return _tm.tm_mon + 1;
	}

	/**
	 * @brief Retorna o dia.
	 * 	
	 * @return int 
	 */
	inline int day() const
	{
		return _tm.tm_mday;
	}

	/**
	 * @brief Retorna a hora.
	 * 
	 * @return int 
	 */
	inline int hour() const
	{
		return _tm.tm_hour;
	}

	/**
	 * @brief 	Retorna o minuto.
	 * 
	 * @return int 
	 */
	inline int minute() const
	{
		return _tm.tm_min;
	}

	/**
	 * @brief Retorna o segundo.
	 * 
	 * @return int 
	 */
	inline int second() const
	{
		return _tm.tm_sec;
	}

	/**
	 * @brief  Retorna o dia da semana.
	 * 
	 * @return int 
	 */
	inline int week() const
	{
		return (_tm.tm_wday > 0) ? _tm.tm_wday : 7;
	}

	/**
	 * @brief  Retorna o dia do ano.
	 * 
	 * @return true 
	 * @return false 
	 */
	inline bool isUTC() const
	{
		return _isUTC;
	}

	/**
	 * @brief Retorna o timestamp.
	 * 
	 * @return time_t 
	 */
	time_t stamp() const;

	/**
	 * @brief  Retorna o timestamp em milisegundos.
	 * 
	 * @return time_t 
	 */
	time_t utcStamp() const;

	/**
	 * @brief  Retorna o timestamp em milisegundos.
	 * 
	 * @return int 
	 */
	int timeZone() const;

    /**
     * @brief  Retorna o timestamp em milisegundos.
     * 
     * @return time_t 
     */
	time_t timeZoneOffset() const;

	/**
	 * @brief  Retorna o timestamp em milisegundos.
	 * 
	 * @param year 
	 * @param month 
	 * @param day 
	 * @param hour 
	 * @param minute 
	 * @param second 
	 * @return Date& 
	 */
	Date & set(int year, int month, int day, int hour, int minute, int second);

	/**
	 * @brief Configura a data.
	 * 
	 * @param year 
	 * @param month 
	 * @param day 
	 * @return Date& 
	 */
	Date & setDate(int year, int month, int day);

	/**
	 * @brief Configura o ano.
	 * 
	 * @param hour 
	 * @param minute 
	 * @param second 
	 * @return Date& 
	 */
	Date & setYear(int year);

	/**
	 * @brief Configura o mês
	 * 
	 * @param month 
	 * @return Date& 
	 */
	Date & setMonth(int month);

	/**
	 * @brief Configura o dia.
	 * 
	 * @param day 
	 * @return Date& 
	 */
	Date & setDay(int day);

	/**
	 * @brief Configura a hora.
	 * 
	 * @param hour 
	 * @return Date& 
	 */
	Date & setHour(int hour);

	/**
	 * @brief Configura o minuto.
	 * 
	 * @param minute 
	 * @return Date& 
	 */
	Date & setMinute(int minute);

	/**
	 * @brief Configura o segundo.
	 * 
	 * @param second 
	 * @return Date& 
	 */
	Date & setSecond(int second);

	/**
	 * @brief Configura o início do período.
	 * @details
	 * 	Para Year, configura o início do ano,
	 * 	Para Month, configura o início do mês,
	 * 	Para Day, configura o início do dia,
	 * 	Para Hour, configura o início da hora,
	 * 	Para Minute, configura o início do minuto,
	 * 	Para Second/MilliSecond/MicroSecond, não tem efeito.
	 * 
	 * @param period
	 * @return Date& 
	 */
	Date & zeroSet(Duration::Period period);

	/**
	 * @brief  Configura o fim do período.
	 * 
	 * @param value 
	 * @param period 
	 * @return Date& 
	 */
	Date & add(int64 value, Duration::Period period);

	/** 
	 * @brief  Configura o fim do período.
	 * 
	 * @param value 
	 * @param period 
	 * @return Date& 
	 */
	Date & add(const Duration & duration);

	/** 
	 * @brief adiciona um ano
	 * 
	 * @param value 
	 * @param period 
	 * @return Date& 
	 */
	Date & addYear(int value);

	/**
	 * @brief Adiciona um mês.
	 * 
	 * @param value 
	 * @return Date& 
	 */
	Date & addMonth(int value);

	/**
	 * @brief  Retorna a diferença entre duas datas.
	 * @param period
	 * 	Para Year, retorna a diferença de anos,
	 * 	Para Month, retorna a diferença de meses,
	 * 	Para Day, retorna a diferença de dias,
	 * 	Para Hour, retorna a diferença de horas,
	 * 	Para Minute, retorna a diferença de minutos,
	 * 	Para Second, retorna a diferença de segundos,
	 * 	Para MilliSecond, retorna a diferença de milisegundos,
	 * 	Para MicroSecond, retorna a diferença de microsegundos.
	 * @param other
	 * @return int64 
	 */
	int64 diff(const Date & other, Duration::Period period = Duration::Second);

	/**
	 * @brief Retorna o dia do ano.
	 * 
	 * @return int 
	 */
	int getYearDay() const;
	/**
	 * @brief Retorna o número de meses desde 1970-01-01 00:00:00.
	 * 
	 * @return int 
	 */
	int getUTCFullMonths() const;
	/**
	 * @brief Retorna o número de anos desde 1970-01-01 00:00:00.
	 * 
	 * @return int 
	 */
	int getUTCFullYears() const;

	/**
	 * @brief Retorna se é ano bissexto.
	 * 
	 * @return true
	 * @return false 
	 */
	bool isLeapYear() const;

	/**
	 * @brief Retorna se é o último dia do mês.
	 * 
	 * @return true
	 * @return false 
	 */
	bool isLastDayOfMonth() const;

	// configura os operadores
	Date operator + (const Duration & duration);
	Date operator - (const Duration & duration);
	Duration operator - (const Date & other);
	Date & operator += (const Duration & duration);
	Date & operator -= (const Duration & duration);
	bool operator < (const Date & other);
	bool operator == (const Date & other);

protected:
	void _set(time_t stamp);
	void _update();

private:
	struct tm _tm;
	bool _isUTC;
};

/**
 * @brief  Representa um período de tempo.
 * 
 */
class Time
{
public:
	Time();
	Time(time_t stamp);
	Time(const Date &date);
	Time(const Time &time);
	~Time();
	Time clone() const;
	/** @brief 转换成本地日历时间的Date对象 */
	/**
	 * @brief Retorna a data.
	 * 
	 * @return Date 
	 */
	Date toDate() const;

	/**
	 * @brief Retorna a data UTC.
	 * 
	 * @return Date 
	 */
	Date utcDate() const;

	/**
	 * @brief Retorna o tempo em segundos.
	 * 
	 * @return time_t 
	 */
	inline time_t seconds() const
	{
		return _tv.tv_sec;
	}

	/**
	 * @brief Retorna o tempo em microsegundos.
	 * 
	 * @return suseconds_t 
	 */
	inline long microSeconds() const
	{
		return _tv.tv_sec;
	}
	inline int64 milliStamp() const
	{
		return _tv.tv_sec * 1000 + _tv.tv_usec / 1000;
	}
	inline int64 microStamp() const
	{
		return _tv.tv_sec * 1000000 + _tv.tv_usec;
	}
	inline time_t stamp() const
	{
		return _tv.tv_sec;
	}
	time_t utcStamp() const;
	Time & set(time_t seconds, long microSeconds = 0);
	Time & setSeconds(time_t seconds);
	Time & setMicroSeconds(long microSeconds);
	Time & zeroSet(Duration::Period period);
	Time & add(int64 value, Duration::Period period = Duration::Period::MilliSecond);
	Time & add(const Duration & duration);
	Time & addWeek(int value);
	Time & addDay(int value);
	Time & addHour(int value);
	Time & addMinute(int value);
	Time & addSecond(long value);
	Time & addMilliSecond(long value);
	Time & addMicroSecond(long value);
	int64 diff(const Time & other, Duration::Period period = Duration::Second);
	int64 getUTCFullMicroSeconds() const;
	int64 getUTCFullMilliSeconds() const;
	time_t getUTCFullSeconds() const;
	int getUTCFullMinutes() const;
	int getUTCFullHours() const;
	int getUTCFullDays() const;
	int getUTCFullWeeks() const;
	// adiciona os operadores
	Time operator + (const Duration & duration);
	Time operator - (const Duration & duration);
	Duration operator - (const Time & other);
	Time & operator += (const Duration & duration);
	Time & operator -= (const Duration & duration);
	bool operator < (const Time & other);
	bool operator = (const Time & other);

private:
	struct timeval _tv;
};

}

#endif