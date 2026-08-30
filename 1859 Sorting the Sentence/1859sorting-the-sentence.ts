function sortSentence(s: string): string {
    let ans: string[] = [];
    s.split(" ").forEach(w => {
        ans[Number(w[w.length - 1]) - 1] = w.slice(0, w.length - 1)
    });
    return ans.join(" ")
};