<!DOCTYPE html>
<html lang = “ja”>

<head>
<meta charset = “UFT-8”>
<title>自動作曲</title>

</head>

<form action="test.php" method="get">
	<select name="bar">
		<option value="8">小節数</option>
		<?php
			for($i = 4; $i < 25; $i++){
				echo "<option value=" . $i . ">" . $i . "</option>";
			}
		?>
	</select>
	<button type="submit">送信</button>
</form>

<tt>
<?php

$bar = $_GET["bar"];
echo $bar . "小節<br>";

for($j = 0; $j < 10; $j++){
	$cmd = "./music.out " . $bar;
	exec($cmd, $opt);
	for($i = 0; $i < $bar; $i++){
		$chord = $opt[$i + (int)$bar * $j];
		echo $chord;
		if($chord === 'C' || $chord === 'F' || $chord === 'G')echo "&nbsp;&nbsp;";
		else echo "&nbsp;";
	}
	echo "<br>";
}

?>
</tt>