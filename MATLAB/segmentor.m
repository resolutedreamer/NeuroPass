%pre-defining matrix to length of ecg in question
% newQRS=zeros(length(ekg1),1);

%% Finding R-peaks
nQRS = nqrsdetect(ekg1,1000);
% HDR1 = qrsdetect(ekg1,1000,1);
% h1QRS = HDR1.EVENT.POS;
% HDR2 = qrsdetect(ekg1,1000,2);
% h2QRS = HDR2.EVENT.POS;

%% Segmentation

% [newQRS] = plotPOS(ekg1,nQRS,newQRS);
% [newQRS] = plotPOS(ekg1,h1QRS,newQRS);
% [newQRS] = plotPOS(ekg1,h2QRS,newQRS);

edges_locs = generate_edges_from_locs(nQRS);
segmented = segment_by_edge(time, ekg1,edges_locs);


% plot em
figure;
plot(time,ekg1)
for j=1:length(segmented)
    hold all;
    plot(segmented{j}(:,1),segmented{j}(:,2))
end
% hold all;
% plot(segmented{length(segmented)}(:,1),segmented{length(segmented)}(:,2), 'green')
% hold all;
% plot(segmented{2}(:,1),segmented{2}(:,2))
% hold all;
% plot(segmented{3}(:,1),segmented{3}(:,2))
% hold all;
% plot(segmented{4}(:,1),segmented{4}(:,2))
% hold all;
% plot(segmented{10}(:,1),segmented{10}(:,2))
% hold all;
% plot(segmented{15}(:,1),segmented{15}(:,2))
title('Beats in an EKG', 'FontWeight','bold')