
class Solution {
public:
    vector<string> splitString(string s, string delim) {
        vector<string> parts;

        uint start = 0;
        int end = s.find(delim);
        while (end != std::string::npos) {
            parts.push_back(s.substr(start, end - start));
            start = end + delim.length();
            end = s.find(delim, start);
        }

        parts.push_back(s.substr(start, end));

        return parts;
    }

    vector<string> subdomainVisits(vector<string>& cpdomains) {
        unordered_map<string, int> domainCounts;

        for (const string& cpdomain : cpdomains) {
            vector<string> parts = splitString(cpdomain, " ");

            int count = stoi(parts[0]);

            string suffix = "";
            vector<string> domainParts = splitString(parts[1], ".");
            for (int i = domainParts.size() - 1; i >= 0; i--) {
                string domain = domainParts[i] + suffix;

                if (domainCounts.find(domain) == domainCounts.end()) {
                    domainCounts[domain] = 0;
                }

                domainCounts[domain] += count;

                suffix = "." + domainParts[i] + suffix;
            }
        }

        vector<string> ret;
        for (const auto& kv : domainCounts) {
            ret.push_back(to_string(kv.second) + " " + kv.first);
        }

        return ret;
    }
};
