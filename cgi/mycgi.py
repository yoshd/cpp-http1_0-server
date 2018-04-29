from datetime import datetime
import io,sys
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

time = datetime.now().strftime("%Y/%m/%d %H:%M:%S")
html = """
<!DOCTYPE html >
<html lang="ja">
<head>
<meta http-equiv="Content-Type" content="text/html;charset=utf-8">
<link rel="stylesheet" type="text/css" href="styles/style.css">
<title>Test CGI</title>
</head>
<body>
<h1>Test CGI</h1>
<p>こんにちは、現在時刻は {} です</p>
</body>
</html>
""".format(time)

print(html)
