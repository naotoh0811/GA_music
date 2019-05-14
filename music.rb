@population = 30 #個体群
@bar = 8 #小節数
@chord = ["C ", "Dm", "Em", "F ", "G ", "Am"]

# ランダムにコード生成
def random_chord_gen(population, bar)
  chord_prog = Array.new(population).map{Array.new(bar, 0)}
  for i in 0..(population-1) do
    for j in 0..(bar-1) do
      chord_prog[i][j] = rand(6)
    end
  end
  return chord_prog
end

# コード進行の評価
def eva_chord(chord_prog)
  #population = chord_prog.length
  #bar = chord_prog[0].length

  for i in 0..(@population-1) do
    # ポイントリセット
    chord_prog[i][@bar] = 50
    point = 0

    # 最初と最後
    if chord_prog[i][0] == 0 && chord_prog[i][@bar-1] == 0 then
      point += 6
    elsif chord_prog[i][0] == 5 && chord_prog[i][@bar-1] == 5 then
      point += 5
    elsif chord_prog[i][0] == 3 && chord_prog[i][@bar-1] == 0 then
      point += 4
    end

    for j in 0..(@bar-2) do
      # 強進行

      # カデンツ

    end

    chord_prog[i][@bar] += point
  end
  return chord_prog
end

# 高得点順に並び替え
def sort_chord(chord_prog)
  chord_prog_sorted = chord_prog.sort {|a, b| b[@bar] <=> a[@bar]}
  return chord_prog_sorted
end

# コード進行のスワップ
def swap_chord

end

# コード進行の表示
def show_chord(chord_prog, point_flag=false)
  #population = chord_prog.length
  #bar = chord_prog[0].length
     
  for i in 0..(@population-1) do
    for j in 0..(@bar-1) do
      # 数字をコードに変換して表示
      print @chord[chord_prog[i][j]]
      if j != (@bar-1) then
        print ", "
      end
    end
    # 点数表示
    if point_flag then
      print " ", chord_prog[i][@bar]
    end
    print "\n"
  end
end

def main()
  chord_prog = random_chord_gen(@population, @bar)
  chord_prog = eva_chord(chord_prog)
  chord_prog = sort_chord(chord_prog)
  show_chord(chord_prog, true)
end

main()