import { $api } from "@/lib/api/client";
import { useState } from "react";
import { Input } from "@/components/ui/input";
import { Button } from "@/components/ui/button";
import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";

export default function RunPage() {
  const [file, setFile] = useState("");
  const [input, setInput] = useState<"prem" | "plain" | "markdown">("prem");
  const [extractor, setExtractor] = useState<"heuristic" | "llm">("heuristic");
  const [stableIds, setStableIds] = useState(true);
  const mutate = $api.useMutation("post", "/api/run");

  const onRun = async () => {
    if (!file) return;
    await mutate.mutateAsync({
      body: { file, input, extractor, stable_ids: stableIds },
    });
  };

  return (
    <Card>
      <CardHeader>
        <CardTitle>Trigger Extraction Run</CardTitle>
      </CardHeader>
      <CardContent className="space-y-3">
        <div>
          <label className="block text-sm mb-1">Source file</label>
          <Input
            value={file}
            onChange={(e) => setFile(e.target.value)}
            placeholder="/absolute/path/to/story.prem"
          />
        </div>
        <div className="flex gap-2">
          <select
            className="border rounded px-2 py-1"
            value={input}
            onChange={(e) => setInput(e.target.value as any)}
          >
            <option value="prem">prem</option>
            <option value="plain">plain</option>
            <option value="markdown">markdown</option>
          </select>
          <select
            className="border rounded px-2 py-1"
            value={extractor}
            onChange={(e) => setExtractor(e.target.value as any)}
          >
            <option value="heuristic">heuristic</option>
            <option value="llm">llm</option>
          </select>
          <label className="flex items-center gap-2 text-sm">
            <input
              type="checkbox"
              checked={stableIds}
              onChange={(e) => setStableIds(e.target.checked)}
            />
            stable ids
          </label>
        </div>
        <Button onClick={onRun} disabled={mutate.isPending}>
          {mutate.isPending ? "Running…" : "Run"}
        </Button>
        {mutate.data && (
          <div className="text-sm text-muted-foreground">
            Updated stats: beats {mutate.data.stats.beats}, facts{" "}
            {mutate.data.stats.facts}
          </div>
        )}
      </CardContent>
    </Card>
  );
}



