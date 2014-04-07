using namespace std;

class ConfigurationFile
{
public:
	static ConfigurationFile& Instance();

	void Set(string key, string value);
	bool Find(const string key);
	string GetValue(const string key);
private:
	ConfigurationFile();
	~ConfigurationFile();
	ConfigurationFile(const ConfigurationFile &) = delete;
	ConfigurationFile& operator = (const ConfigurationFile &) = delete;

	static ConfigurationFile* ConfigFile;
};